#include "TEntity.h"

TEntity::TEntity()
{
	spriteRendererComp = AddComponent<TSpriteRendererComponent>();
	Texture2D t = LoadTexture("../Assets/Entities/entity.png");
	spriteRendererComp->SetTexture(t);
}

void TEntity::Cleanup()
{
	Super::Cleanup();
	return;
}

void TEntity::ReceiveTick()
{
}

void TEntity::Update(float deltaTime)
{
}
