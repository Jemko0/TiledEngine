#pragma once

#include "Engine.h"
#include "TComponent.h"
#include "TTransformComponent.h"

/// <summary>
/// Base Movement component, does not consume input by default
/// </summary>
class ENGINE_API TMovementComponent : public TComponent
{
protected:
	TTransformComponent* m_ParentTransform;
	Vector2 m_Velocity;
	Vector2 m_Bounds;
	Vector2 m_LastInput;

	virtual void Initialize() override;
	virtual void PerformMove(float deltaTime);

public:
	void SetPosition(Vector2 newPos);

	Vector2 GetPosition() const;
	Vector2 GetVelocity() const;
	Vector2 GetBounds() const;
	void AddMovementInput(const Vector2 inputDir);
	Vector2 ConsumeInput();

	virtual void Update(float deltaTime) override;
};