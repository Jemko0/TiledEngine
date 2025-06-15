#include "TTileColliderComponent.h"
#include "TObject.h"
#include "TWorld.h"
#include "TTileMap.h"
#include "TileLookup.h"

void TTileColliderComponent::Update(float deltaTime)
{
    if (!m_MovementComponent) return;

    TTileMap* tileMap = TWorld::Instance().GetScene()->GetTileMap();
    if (!tileMap) return;

    // Get current position and velocity from movement component
    Vector2 currentPosition = m_MovementComponent->GetPosition();
    Vector2 velocity = m_MovementComponent->GetVelocity();
    Vector2 bounds = m_MovementComponent->GetBounds();

    // Calculate next position based on velocity
    Vector2 nextPosition = { currentPosition.x + velocity.x * deltaTime, currentPosition.y + velocity.y * deltaTime };

    // Check and resolve collisions for the next position
    Vector2 resolvedPosition = CheckTileCollisions(tileMap, currentPosition, nextPosition, bounds);

    // Update movement component with the resolved position
    m_MovementComponent->SetPosition(resolvedPosition);
}

void TTileColliderComponent::Initialize()
{
    Super::Initialize();
    m_MovementComponent = m_Owner->GetComponent<TMovementComponent>();
}

Vector2 TTileColliderComponent::CheckTileCollisions(TTileMap* tileMap, Vector2 currentPos, Vector2 nextPos, Vector2 bounds)
{
    const float TILE_SIZE = 32.0f; // Adjust based on your tile size

    Vector2 resolvedPosition = nextPos;

    // Check X-axis collision first
    resolvedPosition.x = CheckAxisCollision(tileMap, currentPos, Vector2{ nextPos.x, currentPos.y }, bounds, true);

    // Then check Y-axis collision
    resolvedPosition.y = CheckAxisCollision(tileMap, Vector2{ resolvedPosition.x, currentPos.y },
        Vector2{ resolvedPosition.x, nextPos.y }, bounds, false);

    return resolvedPosition;
}

float TTileColliderComponent::CheckAxisCollision(TTileMap* tileMap, Vector2 currentPos, Vector2 nextPos,
    Vector2 bounds, bool isXAxis)
{
    const float TILE_SIZE = 32.0f;

    float currentCoord = isXAxis ? currentPos.x : currentPos.y;
    float nextCoord = isXAxis ? nextPos.x : nextPos.y;

    // If not moving on this axis, no collision check needed
    if (currentCoord == nextCoord) return nextCoord;

    // Calculate collision bounds
    float halfWidth = bounds.x * 0.5f;
    float halfHeight = bounds.y * 0.5f;

    Vector2 checkPos = nextPos;

    if (isXAxis) {
        // X-axis collision check
        float left = nextCoord - halfWidth;
        float right = nextCoord + halfWidth;
        float top = checkPos.y - halfHeight;
        float bottom = checkPos.y + halfHeight;

        int startX = (int)(left / TILE_SIZE);
        int endX = (int)(right / TILE_SIZE);
        int startY = (int)(top / TILE_SIZE);
        int endY = (int)(bottom / TILE_SIZE);

        // Clamp to map bounds
        startX = std::max(0, startX);
        endX = std::min(tileMap->width - 1, endX);
        startY = std::max(0, startY);
        endY = std::min(tileMap->height - 1, endY);

        for (int x = startX; x <= endX; x++) {
            for (int y = startY; y <= endY; y++) {
                if (IsSolidTile(tileMap->tiles[x][y])) {
                    float tileLeft = x * TILE_SIZE;
                    float tileRight = (x + 1) * TILE_SIZE;

                    // Check if we're moving right into a wall
                    if (nextCoord > currentCoord && right > tileLeft) {
                        return tileLeft - halfWidth;
                    }
                    // Check if we're moving left into a wall
                    else if (nextCoord < currentCoord && left < tileRight) {
                        return tileRight + halfWidth;
                    }
                }
            }
        }
    }
    else {
        // Y-axis collision check
        float left = checkPos.x - halfWidth;
        float right = checkPos.x + halfWidth;
        float top = nextCoord - halfHeight;
        float bottom = nextCoord + halfHeight;

        int startX = (int)(left / TILE_SIZE);
        int endX = (int)(right / TILE_SIZE);
        int startY = (int)(top / TILE_SIZE);
        int endY = (int)(bottom / TILE_SIZE);

        // Clamp to map bounds
        startX = std::max(0, startX);
        endX = std::min(tileMap->width - 1, endX);
        startY = std::max(0, startY);
        endY = std::min(tileMap->height - 1, endY);

        for (int x = startX; x <= endX; x++) {
            for (int y = startY; y <= endY; y++) {
                if (IsSolidTile(tileMap->tiles[x][y])) {
                    float tileTop = y * TILE_SIZE;
                    float tileBottom = (y + 1) * TILE_SIZE;

                    // Check if we're moving down into a wall
                    if (nextCoord > currentCoord && bottom > tileTop) {
                        return tileTop - halfHeight;
                    }
                    // Check if we're moving up into a wall
                    else if (nextCoord < currentCoord && top < tileBottom) {
                        return tileBottom + halfHeight;
                    }
                }
            }
        }
    }

    return nextCoord; // No collision found
}

bool TTileColliderComponent::IsSolidTile(Tile::ETileType tileType)
{
    return TileLookup::GetTileData(tileType).solid;
}