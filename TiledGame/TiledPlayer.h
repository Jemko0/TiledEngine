#pragma once

#include "Engine.h"
#include "TCharacter.h"

class ENGINE_API TiledPlayer : public TCharacter
{
	typedef TCharacter Super;
public:
	virtual void Initialize() override;
	virtual void Update(float deltaTime) override;
};