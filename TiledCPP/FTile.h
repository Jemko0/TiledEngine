#pragma once

#include "raylib.h"

namespace Tile
{
	enum ETileType
	{
		AIR = 0,
		DIRT,
		GRASS,
		STONE,
		ETileType_MAX,
	};

	struct FTile
	{
	public:
		bool render = true;
		bool solid = true;
		Texture2D* texture;
	};
}