#include "TTileMap.h"
#include "TileLookup.h"

TTileMap::TTileMap(int w, int h)
{
    Initialize(w, h);
}

void TTileMap::Initialize(int w, int h)
{
    width = w;
    height = h;

    tiles.resize(width);

    for (int x = 0; x < width; x++) {
        tiles[x].resize(height, Tile::ETileType::DIRT);
    }

    lightMap.resize(width);

    for (int x = 0; x < width; x++) {
        lightMap[x].resize(height, 0);
    }

    tileFrames.resize(width);

    for (int x = 0; x < width; x++) { 
        tileFrames[x].resize(height, DataTypes::IntVector4{ 0, 0, TILESIZE, TILESIZE });
    }

    LoadAllTileTextures();
}

void TTileMap::BeginDestroy()
{
    Super::BeginDestroy();
}

void TTileMap::Update(float deltaTime)
{
    Super::Update(deltaTime);
}

void TTileMap::LoadTileTexture(Tile::ETileType tileType, const char* texturePath)
{
    m_TileTextures[tileType] = LoadTexture(texturePath);
    SetTextureFilter(m_TileTextures[tileType], TEXTURE_FILTER_POINT);
}

void TTileMap::LoadAllTileTextures()
{
    LoadTileTexture(Tile::ETileType::DIRT, GEngine.GAssetManager->GetAssetPath("Tiles/dirt.png").c_str());
    LoadTileTexture(Tile::ETileType::STONE, GEngine.GAssetManager->GetAssetPath("Tiles/stone.png").c_str());
    LoadTileTexture(Tile::ETileType::GRASS, GEngine.GAssetManager->GetAssetPath("Tiles/grass.png").c_str());
}

bool TTileMap::IsValidTile(int x, int y)
{
    try 
    {
        Tile::ETileType type = tiles.at(x).at(y);
    }
    catch (const std::out_of_range e)
    {
        return false;
    }
    
    return tiles[x][y] != Tile::AIR;
}

bool TTileMap::IsSolidTile(int x, int y)
{
    return TileLookup::GetTileData(tiles[x][y]).solid;
}

Rectangle TTileMap::GetTileRenderPosition(int tx, int ty)
{
    Camera2D* c = TWorld::Instance().GetScene()->activeCamera;
    if (!c) return Rectangle{0, 0, 128, 128};

    Rectangle screenTile = {
        (float)((tx * TILESIZE) - c->target.x), 
        (float)((ty * TILESIZE) - c->target.y), 
        TILESIZE, 
        TILESIZE
    };

    return screenTile;
}

void TTileMap::Render()
{
    RenderWithFrameBatching();
}

void TTileMap::RenderWithFrameBatching()
{
    if (tiles.size() < 1)
    {
        return;
    }

    Rectangle frustum = TWorld::GetScene()->GetCameraFrustum();

    int startX = (int)(frustum.x / TILESIZE);
    int startY = (int)(frustum.y / TILESIZE);
    int endX = (int)((frustum.x + frustum.width) / TILESIZE) + 1;
    int endY = (int)((frustum.y + frustum.height) / TILESIZE) + 1;

    int safeStartX = std::max(0, startX);
    int safeStartY = std::max(0, startY);
    int safeEndX = std::min(width, endX);
    int safeEndY = std::min(height, endY);

    struct FrameKey
    {
        Tile::ETileType tileType = Tile::AIR;
        Rectangle frame;

        bool operator<(const FrameKey& other) const {
            if (tileType != other.tileType) return tileType < other.tileType;
            if (frame.x != other.frame.x) return frame.x < other.frame.x;
            if (frame.y != other.frame.y) return frame.y < other.frame.y;
            if (frame.width != other.frame.width) return frame.width < other.frame.width;
            return frame.height < other.frame.height;
        }
    };

    std::map<FrameKey, std::vector<TileRenderData>> frameBatches;

    for (int x = safeStartX; x < safeEndX; x++)
    {
        for (int y = safeStartY; y < safeEndY; y++)
        {
            if (tiles[x][y] == Tile::ETileType::AIR) continue;

            FrameKey key;
            key.tileType = tiles[x][y];
            key.frame = GetTileFrame(x, y);

            TileRenderData renderData;
            renderData.dest = GetTileRenderPosition(x, y);
            renderData.source = GetTileFrame(x, y);

            renderData.tint = WHITE;
            if (lightMap.size() > 0) {
                float light = lightMap[x][y] / 255.0f;
                renderData.tint = Color{ (unsigned char)(255 * light), (unsigned char)(255 * light), (unsigned char)(255 * light), 255 };
            }

            frameBatches[key].push_back(renderData);
        }
    }

    // Render each unique texture+frame combination
    for (auto& batch : frameBatches)
    {
        const FrameKey& key = batch.first;

        if (m_TileTextures.find(key.tileType) == m_TileTextures.end()) continue;

        Texture2D& texture = m_TileTextures[key.tileType];

        for (const TileRenderData& renderData : batch.second)
        {
            DrawTexturePro(texture,
                renderData.source,
                renderData.dest,
                { 0, 0 },
                0.0f,
                renderData.tint);
        }
    }
}

Rectangle TTileMap::GetTileFrame(int x, int y)
{
    uint8_t frameMask = 0b00000000;

    enum Neighbors : uint8_t
    {
        LEFT    = 1 << 0,
        RIGHT   = 1 << 1,
        UP      = 1 << 2,
        DOWN    = 1 << 3
    };

    if (IsValidTile(x + 1, y)) frameMask |= RIGHT;
    if (IsValidTile(x - 1, y)) frameMask |= LEFT;
    if (IsValidTile(x, y + 1)) frameMask |= DOWN;
    if (IsValidTile(x, y - 1)) frameMask |= UP;
    
    return GetFrameFromMask(frameMask);
}

Rectangle TTileMap::GetFrameFromMask(uint8_t mask)
{
    static const Rectangle frameMap[16] =
    {
        {0 * TILESIZE, 0, TILESIZE, TILESIZE},  // 0000 (0)  - no neighbors (isolated tile)
        {1 * TILESIZE, 0, TILESIZE, TILESIZE},  // 0001 (1)  - right neighbor only
        {2 * TILESIZE, 0, TILESIZE, TILESIZE},  // 0010 (2)  - left neighbor only  
        {3 * TILESIZE, 0, TILESIZE, TILESIZE},  // 0011 (3)  - left + right (horizontal line)

        {0 * TILESIZE, TILESIZE, TILESIZE, TILESIZE},  // 0100 (4)  - down neighbor only
        {1 * TILESIZE, TILESIZE, TILESIZE, TILESIZE},  // 0101 (5)  - right + down (L-shape corner)
        {2 * TILESIZE, TILESIZE, TILESIZE, TILESIZE},  // 0110 (6)  - left + down (reverse L-shape)
        {3 * TILESIZE, TILESIZE, TILESIZE, TILESIZE},  // 0111 (7)  - left + right + down (T-shape up)

        {0 * TILESIZE, 2 * TILESIZE, TILESIZE, TILESIZE},  // 1000 (8)  - up neighbor only
        {1 * TILESIZE, 2 * TILESIZE, TILESIZE, TILESIZE},  // 1001 (9)  - right + up (L-shape corner)
        {2 * TILESIZE, 2 * TILESIZE, TILESIZE, TILESIZE},  // 1010 (10) - left + up (reverse L-shape)
        {3 * TILESIZE, 2 * TILESIZE, TILESIZE, TILESIZE},  // 1011 (11) - left + right + up (T-shape down)

        {0 * TILESIZE, 3 * TILESIZE, TILESIZE, TILESIZE},  // 1100 (12) - up + down (vertical line)
        {1 * TILESIZE, 3 * TILESIZE, TILESIZE, TILESIZE},  // 1101 (13) - right + up + down (T-shape left)
        {2 * TILESIZE, 3 * TILESIZE, TILESIZE, TILESIZE},  // 1110 (14) - left + up + down (T-shape right)
        {3 * TILESIZE, 3 * TILESIZE, TILESIZE, TILESIZE}   // 1111 (15) - all neighbors (cross/center tile)
    };

    return frameMap[mask & 0x0F];
}

void TTileMap::Cleanup()
{
    for (auto& texturePair : m_TileTextures) {
        UnloadTexture(texturePair.second);
    }
    m_TileTextures.clear();
    m_TileBatches.clear();

    tiles.clear();
    tileFrames.clear();
    lightMap.clear();
    Super::Cleanup();
}