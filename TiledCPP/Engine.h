#pragma once

#include "Common.h"
#include "AssetManager.h"
#include "raylib.h"

FORWARD_DECLARE(TWorld);
FORWARD_DECLARE(TScene);

class ENGINE_API Engine
{
private:
    int m_ScreenWidth = 480;
    int m_ScreenHeight = 360;

public:

    TScene* GScene = nullptr;
    AssetManager* GAssetManager = nullptr;

    Engine();
    ~Engine();

    int Init();

private:
    void EngineLoop();
};

extern Engine GEngine;