#pragma once

#include "TMovementComponent.h"

FORWARD_DECLARE(TCharacter);

enum EMovementMode {
	MOVE_NONE,
	MOVE_WALKING,
	MOVE_FALLING,
	MOVE_MAX
};

/// <summary>
/// TCharacterMovementComponent handles collisions with the tilemap and the character before moving
/// </summary>
class ENGINE_API TCharacterMovementComponent : public TMovementComponent
{
protected:
	typedef TMovementComponent Super;
	TCharacter* m_CharacterOwner;
	EMovementMode m_MovementMode;

	float m_Acceleration = 248.0f;
	float m_MaxWalkSpeed = 600.0f;
	float m_TerminalVelocity = 4000.0f;

public:
	virtual void PerformMove(float deltaTime) override;

	void SetCharacter(TCharacter* newChar);
};