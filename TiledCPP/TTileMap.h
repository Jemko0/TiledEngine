#pragma once

#pragma once
#include "raylib.h"
#include "FTile.h"
#include "DataTypes.h"
#include "TObject.h"
#include <vector>
#include <memory>
#include <map>

struct TileRenderData {
    Rectangle dest;
    Rectangle source;
    Color tint;
};

class ENGINE_API TTileMap : public TObject, public IRenderableAsset
{
private:
    std::map<Tile::ETileType, Texture2D> m_TileTextures;
    std::map<Tile::ETileType, std::vector<TileRenderData>> m_TileBatches;

public:
    std::vector<std::vector<Tile::ETileType>> tiles;
    std::vector<std::vector<DataTypes::IntVector4>> tileFrames;
    std::vector<std::vector<int>> lightMap;

    const int TILESIZE = 16;
    const int MAX_LIGHT = 32;

    TTileMap(int w, int h);

    int width, height;

    void Initialize(int w, int h);

    void RenderWithFrameBatching();

    virtual void Cleanup() override;
    virtual void BeginDestroy() override;
    virtual void Update(float deltaTime) override;

    void LoadTileTexture(Tile::ETileType tileType, const char* texturePath);
    void LoadAllTileTextures();

    bool IsSolidTile(int x, int y);

    Rectangle GetTileRenderPosition(int tx, int ty);

    virtual void Render() override;
};