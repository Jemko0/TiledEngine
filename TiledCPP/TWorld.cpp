#include "TWorld.h"

TWorld& TWorld::Instance()
{
    static TWorld instance;
    return instance;
}

TScene* TWorld::NewScene()
{
    Instance().m_Scene = TScene();
    
    if (Instance().m_Scene.activeCamera == nullptr)
    {
        Instance().m_Scene.activeCamera = new Camera2D();
    }

    SetWindowTitle(Instance().m_Scene.GetIdentifier());

    return &Instance().m_Scene;
}

TScene* TWorld::GetScene()
{
    return &Instance().m_Scene;
}