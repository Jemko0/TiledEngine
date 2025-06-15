#include "Input.h"
#include "raylib.h"
#include "TWorld.h"
#include "Mappings.h"

void InputManager::Init()
{
	Mappings::InitializeMappings();
}

void InputManager::Update()
{
	PollInputEvents();

	float lr = 0;
	float ud = 0;

	if (IsKeyDown(KEY_A))
	{
		lr = -1;
	}

	if (IsKeyDown(KEY_D))
	{
		lr = 1;
	}

	if (IsKeyDown(KEY_W))
	{
		ud = 1;
	}

	if (IsKeyDown(KEY_S))
	{
		ud = -1;
	}

	Camera2D* c = TWorld::Instance().GetScene()->activeCamera;

	if (c)
	{
		c->target.x += lr;
		c->target.y += ud;
	}
}