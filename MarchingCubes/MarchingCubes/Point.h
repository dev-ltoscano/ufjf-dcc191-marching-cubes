#pragma once

namespace MarchingCubes
{
	/// <summary>
	/// Ponto 3D
	/// </summary>
	struct Point
	{
		int id;
		float x, y, z;

		Point()
		{
			this->id = -1;
			this->x = 0.0f;
			this->y = 0.0f;
			this->z = 0.0f;
		}

		Point(int id, float x, float y, float z)
		{
			this->id = id;
			this->x = x;
			this->y = y;
			this->z = z;
		}
	};
}