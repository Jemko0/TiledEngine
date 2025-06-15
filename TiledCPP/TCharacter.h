#pragma once

#include "TEntity.h"
#include "TCharacterMovementComponent.h"
#include "TTileColliderComponent.h"

class ENGINE_API TCharacter : public TEntity
{
protected:
	TCharacterMovementComponent* m_MoveComp;
	TTileColliderComponent* m_ColliderComponent;

public:
	TCharacterMovementComponent* GetMovementComponent();
	TTileColliderComponent* GetTileColliderComponent();

	TCharacter();

	virtual void Initialize() override;
	virtual void Update(float deltaTime) override;
};