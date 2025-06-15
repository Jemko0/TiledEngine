#pragma once

#include "Engine.h"

namespace DataTypes
{
	struct IntVector2
	{
	public:
		int x;
		int y;

		IntVector2(int x, int y)
		{
			this->x = x;
			this->y = y;
		}

		IntVector2()
		{
			x = 0;
			y = 0;
		}
	};

	struct IntVector4
	{
	public:
		int x;
		int y;
		int z;
		int w;

		IntVector4(int x, int y, int z, int w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		IntVector4()
		{
			x = 0;
			y = 0;
			z = 0;
			w = 0;
		}
	};
}