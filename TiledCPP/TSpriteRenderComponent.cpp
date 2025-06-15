#include "TSpriteRendererComponent.h"
#include "TObject.h"
#include "TTransformComponent.h"

void TSpriteRendererComponent::Initialize()
{
}

void TSpriteRendererComponent::SetTint(const Color& newTint)
{
	tint = newTint;
}

void TSpriteRendererComponent::SetTexture(const Texture2D tex)
{
	texture = tex;
}

bool TSpriteRendererComponent::CanRender()
{
	return true;
}

void TSpriteRendererComponent::Render()
{
	TTransformComponent* transform = m_Owner->GetComponent<TTransformComponent>();

	Rectangle src = { 0, 0, texture.width, texture.height };
	Rectangle dest = {transform->position.x, transform->position.y, transform->size.x * transform->scale, transform->size.y * transform->scale };

	DrawTexturePro(texture, src, dest, { 0, 0 }, transform->angle, tint);
	//DrawTextureEx(texture, transform->position, transform->angle, transform->scale, tint);
}