#pragma once

#include "Engine.h"
#include "TScene.h"

class ENGINE_API TWorld
{
public:

    static TWorld& Instance();
    static TScene* NewScene();
    static TScene* GetScene();

    TWorld(const TWorld&) = delete;
    TWorld& operator=(const TWorld&) = delete;
    TWorld(TWorld&&) = delete;
    TWorld& operator=(TWorld&&) = delete;

private:
    TWorld() = default;
    TScene m_Scene;
};