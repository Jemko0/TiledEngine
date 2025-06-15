#pragma once

#include "Engine.h"
#include "TPlaceable.h"
#include "TSpriteRendererComponent.h"

/// <summary>
/// TEntity is a class for objects that can render in the world
/// </summary>
class ENGINE_API TEntity : public TPlaceable
{
public:
	typedef TPlaceable Super;
	TSpriteRendererComponent* spriteRendererComp;

	TEntity();
	virtual void Cleanup() override;
	virtual void ReceiveTick() override;
	virtual void Update(float deltaTime) override;
};