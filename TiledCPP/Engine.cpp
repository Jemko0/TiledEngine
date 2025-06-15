#include "Engine.h"
#include "TWorld.h"
#include "TScene.h"
#include "Input.h"

Engine GEngine;

Engine::Engine()
{
    GAssetManager = new AssetManager();
}

Engine::~Engine()
{
    delete GAssetManager;
}

int Engine::Init()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(m_ScreenWidth, m_ScreenHeight, "Tiled");
    SetWindowTitle("Tiled Engine");
    SetTargetFPS(144);

    GScene = TWorld::NewScene();
    GScene->Init();

    while (!WindowShouldClose())
    {
        EngineLoop();
    }

    delete GScene;

    CloseWindow();
    return 0;
}

void Engine::EngineLoop()
{
    InputManager::Init();
    InputManager::Update();

    BeginDrawing();

    GScene->Update(GetFrameTime());
    GScene->Render();

    DrawText(FTEXT("Camera: X: %f Y: %f", GScene->activeCamera->target.x, GScene->activeCamera->target.y), 32, 32, 24, WHITE);

    EndDrawing();
}