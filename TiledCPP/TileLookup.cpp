#include "TileLookup.h"
#include "Engine.h"

Tile::FTile TileLookup::GetTileData(Tile::ETileType& type)
{
	Tile::FTile t = Tile::FTile();

	t.render = true;
	t.solid = true;
	t.texture = LoadTexture(AssetManager::GetAssetPath("Tiles/DebugTile.png").c_str());
	switch (type)
	{
	case Tile::AIR:
		t.render = false;
		t.solid = false;
		break;

	case Tile::DIRT:

		break;

	case Tile::GRASS:

		break;

	case Tile::STONE:

		break;

	case Tile::ETileType_MAX:
		break;

	default:
		break;
	}

	return t;
}
