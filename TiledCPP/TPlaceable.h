#pragma once

#include "TObject.h"
#include "TTransformComponent.h"

/// <summary>
/// TPlaceable is the base class of TObjects that can be placed in a scene
/// </summary>
class ENGINE_API TPlaceable : public TObject
{
public:
	typedef TObject Super;

	TPlaceable();
	
	TTransformComponent* transform = nullptr;

	virtual void Update(float deltaTime) override;

	virtual void ReceiveTick() = 0;
	virtual void Cleanup() override;
};