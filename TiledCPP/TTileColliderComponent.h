#pragma once
#include "TComponent.h"
#include "TMovementComponent.h"
#include "FTile.h"

// Forward declarations
FORWARD_DECLARE(TTileMap);

class ENGINE_API TTileColliderComponent : TComponent
{
private:
    TMovementComponent* m_MovementComponent;

    // Helper methods for collision detection
    Vector2 CheckTileCollisions(TTileMap* tileMap, Vector2 currentPos, Vector2 nextPos, Vector2 bounds);
    float CheckAxisCollision(TTileMap* tileMap, Vector2 currentPos, Vector2 nextPos, Vector2 bounds, bool isXAxis);
    bool IsSolidTile(Tile::ETileType tileType);
    

public:
    virtual void Update(float deltaTime) override;
    virtual void Initialize() override;
};