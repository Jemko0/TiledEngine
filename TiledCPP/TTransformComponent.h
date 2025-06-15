#pragma once

#include "Engine.h"
#include "TComponent.h"
#include "DataTypes.h"

class ENGINE_API TTransformComponent : public TComponent
{
public:
	Vector2 position = {0.0f, 0.0f};
	float angle = 0.0f;
	Vector2 size = {10.0f, 10.0f};
	float scale = 0.0f;

	virtual void Initialize() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual bool CanRender() override;

	Vector2 GetScaledBounds();
};