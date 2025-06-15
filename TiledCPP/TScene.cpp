#include "TScene.h"
#include "TObject.h"
#include "Input.h"
#include "TEntity.h"
#include "TTileMap.h"

TScene::TScene()
{
    m_Identifier = GenerateIdentifier();
}

TScene::~TScene()
{
    if (activeCamera != nullptr)
    {
        delete activeCamera;
    }

    for (TObject*& o : m_Objects)
    {
        o->BeginDestroy();
    }
}

const char* TScene::GenerateIdentifier()
{
    static const char chars[] = "abcdefghijklmnopqrstuvwxyz0123456789";
    static char buffer[16];
    
    for (int i = 0; i < 15; ++i)
    {
        buffer[i] = chars[rand() % (sizeof(chars) - 1)];
    }

    buffer[15] = '\0';
    
    return buffer;
}

std::vector<TObject*>& TScene::GetObjects()
{
	return m_Objects;
}

bool TScene::RegisterObject(TObject* o)
{
	if (!o)
	{
		return false;
	}
	m_Objects.push_back(o);

	return true;
}

bool TScene::UnregisterObject(TObject* o)
{
    if (!o)
    {
        return false;
    }

    std::vector<TObject*>::iterator it = std::find(m_Objects.begin(), m_Objects.end(), o);
    if (it != m_Objects.end())
    {
        m_Objects.erase(it);
        return true;
    }

    return false;
}

const char* TScene::GetIdentifier()
{
    return m_Identifier;
}

TTileMap* TScene::InitTileMap(int w, int h)
{
    m_Tilemap = new TTileMap(w, h);
    return m_Tilemap;
}

TTileMap* TScene::GetTileMap()
{
    return m_Tilemap;
}

void TScene::DestroyTileMap()
{
    m_Tilemap->Cleanup();
    m_Tilemap->BeginDestroy();
}

Rectangle TScene::GetCameraFrustum()
{
    if (!activeCamera) return Rectangle();

    return Rectangle{ activeCamera->target.x, activeCamera->target.y, (float)GetScreenWidth(), (float)GetScreenHeight() };
}

void TScene::Init()
{
    InitTileMap(2000, 4000);
}

void TScene::Update(float deltaTime)
{
    for (auto it = m_Objects.begin(); it != m_Objects.end();)
    {
        TObject* o = *it;
        if (o->bPendingDestroy)
        {
            o->Cleanup();
            it = m_Objects.erase(it);
            delete o;
            continue;
        }

        o->Update(deltaTime);
        it++;
    }
}

void TScene::Render()
{
    ClearBackground(RED);

    if (m_Tilemap)
    {
        m_Tilemap->Render();
    }

    if (m_Objects.empty())
    {
        return;
    }

    for (TObject* o : m_Objects)
    {
        for (std::unique_ptr<TComponent>& c : *o->GetComponents())
        {
            if (c->CanRender())
            {
                c->Render();
            }
        }
    }
}
