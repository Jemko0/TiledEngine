#pragma once

#include "Engine.h"
#include "TObject.h"
#include "TCharacter.h"

/// <summary>
/// Controller, handles input mapping binding and can possess characters
/// </summary>
class ENGINE_API Controller : public TPlaceable
{
	TCharacter* m_PossessedCharacter;
	Camera2D* m_ActiveCamera;
	bool m_AttachCameraToCharacter = true;

public:
	void SetAttachCameraToCharacter(bool attach);
	void Initialize() override;
	virtual void SetupBindings();

	void Possess(TCharacter* pChar);
	void Unpossess();

	virtual void Update(float deltaTime) override;
};