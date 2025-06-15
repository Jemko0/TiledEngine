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

	Camera2D* c = TWorld::Instance().GetScene()->activeCamera;

	if (c)
	{
		c->target.x += lr;
		c->target.y += ud;
	}
}