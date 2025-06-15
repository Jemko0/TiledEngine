#include "TTileMap.h"

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

bool TTileMap::IsSolidTile(int x, int y)
{
    return tiles[x][y];
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

    struct FrameKey {
        Tile::ETileType tileType = Tile::AIR;
        DataTypes::IntVector4 frame;

        bool operator<(const FrameKey& other) const {
            if (tileType != other.tileType) return tileType < other.tileType;
            if (frame.x != other.frame.x) return frame.x < other.frame.x;
            if (frame.y != other.frame.y) return frame.y < other.frame.y;
            if (frame.z != other.frame.z) return frame.z < other.frame.z;
            return frame.w < other.frame.w;
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
            key.frame = tileFrames[x][y];

            TileRenderData renderData;
            renderData.dest = GetTileRenderPosition(x, y);
            renderData.source = { (float)key.frame.x, (float)key.frame.y, (float)key.frame.z, (float)key.frame.w };

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
        Rectangle source = { key.frame.x, key.frame.y, key.frame.z, key.frame.w };

        for (const TileRenderData& renderData : batch.second)
        {
            DrawTexturePro(texture,
                source,
                renderData.dest,
                { 0, 0 },
                0.0f,
                renderData.tint);
        }
    }
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