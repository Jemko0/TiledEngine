#include "TCharacter.h"

TCharacterMovementComponent* TCharacter::GetMovementComponent()
{
    return m_MoveComp;
}

TTileColliderComponent* TCharacter::GetTileColliderComponent()
{
    return m_ColliderComponent;
}

TCharacter::TCharacter()
{
    m_MoveComp = AddComponent<TCharacterMovementComponent>();
    m_MoveComp->SetCharacter(this);
}

void TCharacter::Initialize()
{
}

void TCharacter::Update(float deltaTime)
{
}
