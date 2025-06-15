#include "Controller.h"

void Controller::SetAttachCameraToCharacter(bool attach)
{
	m_AttachCameraToCharacter = attach;
}

void Controller::Initialize()
{
	SetupBindings();
}

void Controller::SetupBindings()
{
}

void Controller::Possess(TCharacter* pChar)
{
	m_PossessedCharacter = pChar;
}

void Controller::Unpossess()
{
	//detach from character but dont destroy
	m_PossessedCharacter = nullptr;
}

void Controller::Update(float deltaTime)
{
	if (!m_AttachCameraToCharacter) return;
	if (!m_PossessedCharacter) return;

	if (m_AttachCameraToCharacter)
	{
		m_ActiveCamera->target = m_PossessedCharacter->transform->position;
	}
	
	Super::Update(deltaTime);
}