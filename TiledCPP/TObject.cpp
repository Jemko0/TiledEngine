#include "TObject.h"
#include "TScene.h"
#include "TWorld.h"

void TObject::SetScene(TScene& scene)
{
	m_ParentScene = &scene;
}

void TObject::BeginDestroy()
{
	bPendingDestroy = true;
}

void TObject::Cleanup()
{
	return;
}

void TObject::Initialize()
{
}

std::vector<std::unique_ptr<TComponent>>* TObject::GetComponents()
{
	return &m_Components;
}

/// <summary>
/// Handles updates, by default will update components
/// </summary>
/// <param name="deltaTime"></param>
void TObject::Update(float deltaTime)
{
	for (std::unique_ptr<TComponent>& c : m_Components)
	{
		c->Update(deltaTime);
		if (c->CanRender())
		{
			c->Render();
		}
	}
}