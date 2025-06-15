#include "TCharacterMovementComponent.h"
#include "TCharacter.h"

void TCharacterMovementComponent::PerformMove(float deltaTime)
{
	Vector2 input = ConsumeInput();

	if (m_CharacterOwner)
	{
		TTileColliderComponent* colliderComp = m_CharacterOwner->GetTileColliderComponent();
		if (colliderComp)
		{
			colliderComp->Update(deltaTime);
		}
	}

	m_Velocity.x += m_Acceleration * input.x * deltaTime;
	m_Velocity.y += m_Acceleration * input.y * deltaTime;
	Super::PerformMove(deltaTime);
}

void TCharacterMovementComponent::SetCharacter(TCharacter* newChar)
{
	m_CharacterOwner = newChar;
}
