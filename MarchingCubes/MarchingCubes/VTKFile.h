#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "Point.h"
#include "GridDomain.h"
#include "LogHelper.h"

using namespace std;

namespace MarchingCubes
{
	/// <summary>
	/// Linha que une dois pontos no arquivo VTK
	/// </summary>
	struct Line
	{
		int startPointIndex, endPointIndex;

		Line()
		{
			this->startPointIndex = -1;
			this->endPointIndex = -1;
		}

		Line(int startPointIndex, int endPointIndex)
		{
			this->startPointIndex = startPointIndex;
			this->endPointIndex = endPointIndex;
		}
	};

	struct Polygon
	{
		vector<int> vertexIndexVect;
	};

	/// <summary>
	/// Dimensão do domínio no arquivo VTK
	/// </summary>
	struct Dimension
	{
		int xDim, yDim, zDim;

		Dimension()
		{
			this->xDim = -1;
			this->yDim = -1;
			this->zDim = -1;
		}

		Dimension(int xDim, int yDim, int zDim)
		{
			this->xDim = xDim;
			this->yDim = yDim;
			this->zDim = zDim;
		}
	};

	/// <summary>
	/// Espaçamento entre pontos do domínio no arquivo VTK
	/// </summary>
	struct Spacing
	{
		float xSpacing, ySpacing, zSpacing;

		Spacing()
		{
			this->xSpacing = -1.0f;
			this->ySpacing = -1.0f;
			this->zSpacing = -1.0f;
		}

		Spacing(float xSpacing, float ySpacing, float zSpacing)
		{
			this->xSpacing = xSpacing;
			this->ySpacing = ySpacing;
			this->zSpacing = zSpacing;
		}
	};

	/// <summary>
	/// Estrutura do arquivo VTK
	/// </summary>
	class VTKFile
	{
	private:
		Dimension dimension;
		Point originPoint;
		Spacing spacing;
		int pointDataCount;
		vector<Point> pointVector;
		vector<Line> lineVector;
		vector<float> scalarVector;

		int polygonDataCount = 0;
		vector<Polygon> polygonVector;

		static vector<string> tokenizer(const string& p_pcstStr, char delim);
	public:
		static VTKFile* loadFile(string filePath);
		void saveVTK(string filePath);

		GridDomain* toGridDomain();

		void insertPoint(Point &point);
		void insertLine(Line &line);
		void insertPolygon(Polygon &p);
	};
}