#pragma once

#include <vector>
#include "Point.h"

using namespace std;

namespace MarchingCubes
{
	struct GridCell
	{
		int id;

		// Pontos dos vértices da célula
		Point v0, v1, v2, v3, v4, v5, v6, v7;

		// Valores de escalar associdados aos vértices da célula
		float s0, s1, s2, s3, s4, s5, s6, s7;
	};

	struct GridDomain
	{
		vector<GridCell> cellVector;
	};
}