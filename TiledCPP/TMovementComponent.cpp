#include "TMovementComponent.h"
#include "TObject.h"

void TMovementComponent::Initialize()
{
	m_ParentTransform = m_Owner->GetComponent<TTransformComponent>();
	m_Bounds = m_ParentTransform->GetScaledBounds();
}

void TMovementComponent::Update(float deltaTime)
{
	PerformMove(deltaTime);
}

void TMovementComponent::PerformMove(float deltaTime)
{
	if (m_ParentTransform)
	{
		m_ParentTransform->position.x += GetVelocity().x;
		m_ParentTransform->position.y += GetVelocity().y;
	}
}

void TMovementComponent::SetPosition(Vector2 newPos)
{
	m_ParentTransform->position = newPos;
}

Vector2 TMovementComponent::GetPosition() const
{
	return m_ParentTransform->position;
}

Vector2 TMovementComponent::GetVelocity() const
{
	return m_Velocity;
}

/// <summary>
/// When calling this, it should be scaled bounds
/// </summary>
/// <returns></returns>
Vector2 TMovementComponent::GetBounds() const
{
	return m_Bounds;
}

void TMovementComponent::AddMovementInput(const Vector2 inputDir)
{
	m_LastInput = inputDir;
}

Vector2 TMovementComponent::ConsumeInput()
{
	Vector2 v = m_LastInput;
	m_LastInput = {0, 0};
	return v;
}