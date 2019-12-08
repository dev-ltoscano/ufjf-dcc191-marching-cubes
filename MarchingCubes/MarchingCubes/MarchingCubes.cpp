#include <iostream>
#include <string>

#include "VTKFile.h"
#include "GridDomain.h"

#define BIT_0			0
#define BIT_1			1

using namespace std;
using namespace MarchingCubes;

int calculateCaseIndex(bool *binaryCode)
{
	int caseIndex = 0;

	caseIndex += binaryCode[0] * pow(2, 0);
	caseIndex += binaryCode[1] * pow(2, 1);
	caseIndex += binaryCode[2] * pow(2, 2);
	caseIndex += binaryCode[3] * pow(2, 3);
	caseIndex += binaryCode[4] * pow(2, 4);
	caseIndex += binaryCode[5] * pow(2, 5);
	caseIndex += binaryCode[6] * pow(2, 6);
	caseIndex += binaryCode[7] * pow(2, 7);

	return caseIndex;
}

int main(int argc, char **argv)
{
	if (argc < 4)
	{
		std::cout << "Parameter: <vtkFilePath> <scalarValue> <outFilePath>" << endl;
	}

	string vtkFilePath = argv[1];
	float scalarValue = atof(argv[2]);
	string outFilePath = argv[3];

	std::cout << "Loading VTK file..." << endl;
	VTKFile *vtkFile = VTKFile::loadFile(vtkFilePath);

	std::cout << "Building cell grid..." << endl;
	GridDomain *gridDomain = vtkFile->toGridDomain();

	VTKFile *vtkCountour = new VTKFile();
	bool *binaryCode = new bool[8];
	GridCell *gridCell;
	int caseKey;

	int pointIndex = 0;
	float p_value;
	int p0Index, p1Index, p2Index, p3Index, p4Index, p5Index, p6Index, p7Index, p8Index;

	std::cout << "Calculating the contour... [ Total cells: " << gridDomain->cellVector.size() << "]" << endl;

	for (int i = 0; i < gridDomain->cellVector.size(); i++)
	{
		gridCell = &gridDomain->cellVector[i];

		binaryCode[0] = (gridCell->s0 > scalarValue) ? BIT_1 : BIT_0;
		binaryCode[1] = (gridCell->s1 > scalarValue) ? BIT_1 : BIT_0;
		binaryCode[2] = (gridCell->s2 > scalarValue) ? BIT_1 : BIT_0;
		binaryCode[3] = (gridCell->s3 > scalarValue) ? BIT_1 : BIT_0;
		binaryCode[4] = (gridCell->s4 > scalarValue) ? BIT_1 : BIT_0;
		binaryCode[5] = (gridCell->s5 > scalarValue) ? BIT_1 : BIT_0;
		binaryCode[6] = (gridCell->s6 > scalarValue) ? BIT_1 : BIT_0;
		binaryCode[7] = (gridCell->s7 > scalarValue) ? BIT_1 : BIT_0;

		caseKey = calculateCaseIndex(binaryCode);

		switch (caseKey)
		{
		case 1: // 00000001
		{
			p0Index = pointIndex++;
			p_value = (((gridCell->v0.z * (gridCell->s1 - scalarValue)) + (gridCell->v1.z * (scalarValue - gridCell->s0))) / (gridCell->s1 - gridCell->s0));
			vtkCountour->insertPoint(Point(p0Index, gridCell->v0.x, gridCell->v0.y, p_value));

			p1Index = pointIndex++;
			p_value = (((gridCell->v3.x * (gridCell->s0 - scalarValue)) + (gridCell->v0.x * (scalarValue - gridCell->s3))) / (gridCell->s0 - gridCell->s3));
			vtkCountour->insertPoint(Point(p1Index, p_value, gridCell->v3.y, gridCell->v3.z));

			p2Index = pointIndex++;
			p_value = (((gridCell->v0.y * (gridCell->s4 - scalarValue)) + (gridCell->v4.y * (scalarValue - gridCell->s0))) / (gridCell->s4 - gridCell->s0));
			vtkCountour->insertPoint(Point(p2Index, gridCell->v0.x, p_value, gridCell->v0.z));

			/*Polygon p;

			p.vertexIndexVect.push_back(p0Index);
			p.vertexIndexVect.push_back(p1Index);
			p.vertexIndexVect.push_back(p2Index);

			vtkCountour->insertPolygon(p);*/
			break;
		}
		case 3: // 00000011
		{
			p0Index = pointIndex++;
			p_value = (((gridCell->v1.x * (gridCell->s2 - scalarValue)) + (gridCell->v2.x * (scalarValue - gridCell->s1))) / (gridCell->s2 - gridCell->s1));
			vtkCountour->insertPoint(Point(p0Index, p_value, gridCell->v1.y, gridCell->v1.z));

			p1Index = pointIndex++;
			p_value = (((gridCell->v3.x * (gridCell->s0 - scalarValue)) + (gridCell->v0.x * (scalarValue - gridCell->s3))) / (gridCell->s0 - gridCell->s3));
			vtkCountour->insertPoint(Point(p1Index, p_value, gridCell->v3.y, gridCell->v3.z));

			p2Index = pointIndex++;
			p_value = (((gridCell->v0.y * (gridCell->s4 - scalarValue)) + (gridCell->v4.y * (scalarValue - gridCell->s0))) / (gridCell->s4 - gridCell->s0));
			vtkCountour->insertPoint(Point(p2Index, gridCell->v0.x, p_value, gridCell->v0.z));

			p3Index = pointIndex++;
			p_value = (((gridCell->v1.y * (gridCell->s5 - scalarValue)) + (gridCell->v5.y * (scalarValue - gridCell->s1))) / (gridCell->s5 - gridCell->s1));
			vtkCountour->insertPoint(Point(p3Index, gridCell->v1.x, p_value, gridCell->v1.z));

			/*Polygon p;

			p.vertexIndexVect.push_back(p0Index);
			p.vertexIndexVect.push_back(p1Index);
			p.vertexIndexVect.push_back(p2Index);
			p.vertexIndexVect.push_back(p3Index);

			vtkCountour->insertPolygon(p);*/
			break;
		}
		case 33: // 00100001
		{
			p0Index = pointIndex++;
			p_value = (((gridCell->v0.z * (gridCell->s1 - scalarValue)) + (gridCell->v1.z * (scalarValue - gridCell->s0))) / (gridCell->s1 - gridCell->s0));
			vtkCountour->insertPoint(Point(p0Index, gridCell->v0.x, gridCell->v0.y, p_value));

			p1Index = pointIndex++;
			p_value = (((gridCell->v3.x * (gridCell->s0 - scalarValue)) + (gridCell->v0.x * (scalarValue - gridCell->s3))) / (gridCell->s0 - gridCell->s3));
			vtkCountour->insertPoint(Point(p1Index, p_value, gridCell->v3.y, gridCell->v3.z));

			p2Index = pointIndex++;
			p_value = (((gridCell->v0.y * (gridCell->s4 - scalarValue)) + (gridCell->v4.y * (scalarValue - gridCell->s0))) / (gridCell->s4 - gridCell->s0));
			vtkCountour->insertPoint(Point(p2Index, gridCell->v0.x, p_value, gridCell->v0.z));

			p3Index = pointIndex++;
			p_value = (((gridCell->v4.z * (gridCell->s5 - scalarValue)) + (gridCell->v5.z * (scalarValue - gridCell->s4))) / (gridCell->s5 - gridCell->s4));
			vtkCountour->insertPoint(Point(p3Index, gridCell->v4.x, gridCell->v4.y, p_value));

			p4Index = pointIndex++;
			p_value = (((gridCell->v5.x * (gridCell->s6 - scalarValue)) + (gridCell->v6.x * (scalarValue - gridCell->s5))) / (gridCell->s6 - gridCell->s5));
			vtkCountour->insertPoint(Point(p4Index, p_value, gridCell->v5.y, gridCell->v5.z));

			p5Index = pointIndex++;
			p_value = (((gridCell->v1.y * (gridCell->s5 - scalarValue)) + (gridCell->v5.y * (scalarValue - gridCell->s1))) / (gridCell->s5 - gridCell->s1));
			vtkCountour->insertPoint(Point(p5Index, gridCell->v1.x, p_value, gridCell->v1.z));

			/*Polygon p0;

			p0.vertexIndexVect.push_back(p0Index);
			p0.vertexIndexVect.push_back(p1Index);
			p0.vertexIndexVect.push_back(p2Index);

			vtkCountour->insertPolygon(p0);

			Polygon p1;

			p1.vertexIndexVect.push_back(p3Index);
			p1.vertexIndexVect.push_back(p4Index);
			p1.vertexIndexVect.push_back(p5Index);

			vtkCountour->insertPolygon(p1);*/
			break;
		}
		case 65: // 01000001
		{
			p0Index = pointIndex++;
			p_value = (((gridCell->v0.z * (gridCell->s1 - scalarValue)) + (gridCell->v1.z * (scalarValue - gridCell->s0))) / (gridCell->s1 - gridCell->s0));
			vtkCountour->insertPoint(Point(p0Index, gridCell->v0.x, gridCell->v0.y, p_value));

			p1Index = pointIndex++;
			p_value = (((gridCell->v3.x * (gridCell->s0 - scalarValue)) + (gridCell->v0.x * (scalarValue - gridCell->s3))) / (gridCell->s0 - gridCell->s3));
			vtkCountour->insertPoint(Point(p1Index, p_value, gridCell->v3.y, gridCell->v3.z));

			p2Index = pointIndex++;
			p_value = (((gridCell->v0.y * (gridCell->s4 - scalarValue)) + (gridCell->v4.y * (scalarValue - gridCell->s0))) / (gridCell->s4 - gridCell->s0));
			vtkCountour->insertPoint(Point(p2Index, gridCell->v0.x, p_value, gridCell->v0.z));

			p3Index = pointIndex++;
			p_value = (((gridCell->v5.x * (gridCell->s6 - scalarValue)) + (gridCell->v6.x * (scalarValue - gridCell->s5))) / (gridCell->s6 - gridCell->s5));
			vtkCountour->insertPoint(Point(p3Index, p_value, gridCell->v5.y, gridCell->v5.z));

			p4Index = pointIndex++;
			p_value = (((gridCell->v6.z * (gridCell->s7 - scalarValue)) + (gridCell->v7.z * (scalarValue - gridCell->s6))) / (gridCell->s7 - gridCell->s6));
			vtkCountour->insertPoint(Point(p4Index, gridCell->v6.x, gridCell->v6.y, p_value));

			p5Index = pointIndex++;
			p_value = (((gridCell->v2.y * (gridCell->s6 - scalarValue)) + (gridCell->v6.y * (scalarValue - gridCell->s2))) / (gridCell->s6 - gridCell->s2));
			vtkCountour->insertPoint(Point(p5Index, gridCell->v2.x, p_value, gridCell->v2.z));

			/*Polygon p0;

			p0.vertexIndexVect.push_back(p0Index);
			p0.vertexIndexVect.push_back(p1Index);
			p0.vertexIndexVect.push_back(p2Index);

			vtkCountour->insertPolygon(p0);

			Polygon p1;

			p1.vertexIndexVect.push_back(p3Index);
			p1.vertexIndexVect.push_back(p4Index);
			p1.vertexIndexVect.push_back(p5Index);

			vtkCountour->insertPolygon(p1);*/
			break;
		}
		case 14: // 00001110
		{
			p0Index = pointIndex++;
			p_value = (((gridCell->v0.z * (gridCell->s1 - scalarValue)) + (gridCell->v1.z * (scalarValue - gridCell->s0))) / (gridCell->s1 - gridCell->s0));
			vtkCountour->insertPoint(Point(p0Index, gridCell->v0.x, gridCell->v0.y, p_value));

			p1Index = pointIndex++;
			p_value = (((gridCell->v3.x * (gridCell->s0 - scalarValue)) + (gridCell->v0.x * (scalarValue - gridCell->s3))) / (gridCell->s0 - gridCell->s3));
			vtkCountour->insertPoint(Point(p1Index, p_value, gridCell->v3.y, gridCell->v3.z));

			p2Index = pointIndex++;
			p_value = (((gridCell->v1.y * (gridCell->s5 - scalarValue)) + (gridCell->v5.y * (scalarValue - gridCell->s1))) / (gridCell->s5 - gridCell->s1));
			vtkCountour->insertPoint(Point(p2Index, gridCell->v1.x, p_value, gridCell->v1.z));
			
			p3Index = pointIndex++;
			p_value = (((gridCell->v2.y * (gridCell->s6 - scalarValue)) + (gridCell->v6.y * (scalarValue - gridCell->s2))) / (gridCell->s6 - gridCell->s2));
			vtkCountour->insertPoint(Point(p3Index, gridCell->v2.x, p_value, gridCell->v2.z));

			p4Index = pointIndex++;
			p_value = (((gridCell->v3.y * (gridCell->s7 - scalarValue)) + (gridCell->v7.y * (scalarValue - gridCell->s3))) / (gridCell->s7 - gridCell->s3));
			vtkCountour->insertPoint(Point(p4Index, gridCell->v3.x, p_value, gridCell->v3.z));

			/*Polygon p;

			p.vertexIndexVect.push_back(p0Index);
			p.vertexIndexVect.push_back(p1Index);
			p.vertexIndexVect.push_back(p2Index);
			p.vertexIndexVect.push_back(p3Index);
			p.vertexIndexVect.push_back(p4Index);

			vtkCountour->insertPolygon(p);*/
			break;
		}
		case 67: // 01000011
		{
			p0Index = pointIndex++;
			p_value = (((gridCell->v1.x * (gridCell->s2 - scalarValue)) + (gridCell->v2.x * (scalarValue - gridCell->s1))) / (gridCell->s2 - gridCell->s1));
			vtkCountour->insertPoint(Point(p0Index, p_value, gridCell->v1.y, gridCell->v1.z));

			p1Index = pointIndex++;
			p_value = (((gridCell->v3.x * (gridCell->s0 - scalarValue)) + (gridCell->v0.x * (scalarValue - gridCell->s3))) / (gridCell->s0 - gridCell->s3));
			vtkCountour->insertPoint(Point(p1Index, p_value, gridCell->v3.y, gridCell->v3.z));

			p2Index = pointIndex++;
			p_value = (((gridCell->v0.y * (gridCell->s4 - scalarValue)) + (gridCell->v4.y * (scalarValue - gridCell->s0))) / (gridCell->s4 - gridCell->s0));
			vtkCountour->insertPoint(Point(p2Index, gridCell->v0.x, p_value, gridCell->v0.z));

			p3Index = pointIndex++;
			p_value = (((gridCell->v1.y * (gridCell->s5 - scalarValue)) + (gridCell->v5.y * (scalarValue - gridCell->s1))) / (gridCell->s5 - gridCell->s1));
			vtkCountour->insertPoint(Point(p3Index, gridCell->v1.x, p_value, gridCell->v1.z));

			p4Index = pointIndex++;
			p_value = (((gridCell->v5.x * (gridCell->s6 - scalarValue)) + (gridCell->v6.x * (scalarValue - gridCell->s5))) / (gridCell->s6 - gridCell->s5));
			vtkCountour->insertPoint(Point(p4Index, p_value, gridCell->v5.y, gridCell->v5.z));

			p5Index = pointIndex++;
			p_value = (((gridCell->v6.z * (gridCell->s7 - scalarValue)) + (gridCell->v7.z * (scalarValue - gridCell->s6))) / (gridCell->s7 - gridCell->s6));
			vtkCountour->insertPoint(Point(p5Index, gridCell->v6.x, gridCell->v6.y, p_value));

			p6Index = pointIndex++;
			p_value = (((gridCell->v2.y * (gridCell->s6 - scalarValue)) + (gridCell->v6.y * (scalarValue - gridCell->s2))) / (gridCell->s6 - gridCell->s2));
			vtkCountour->insertPoint(Point(p6Index, gridCell->v2.x, p_value, gridCell->v2.z));

			/*Polygon p0;

			p0.vertexIndexVect.push_back(p0Index);
			p0.vertexIndexVect.push_back(p1Index);
			p0.vertexIndexVect.push_back(p2Index);
			p0.vertexIndexVect.push_back(p3Index);

			vtkCountour->insertPolygon(p0);

			Polygon p1;

			p1.vertexIndexVect.push_back(p4Index);
			p1.vertexIndexVect.push_back(p5Index);
			p1.vertexIndexVect.push_back(p6Index);

			vtkCountour->insertPolygon(p1);*/
			break;
		}
		case 82: // 01010010
		{
			p0Index = pointIndex++;
			p_value = (((gridCell->v0.z * (gridCell->s1 - scalarValue)) + (gridCell->v1.z * (scalarValue - gridCell->s0))) / (gridCell->s1 - gridCell->s0));
			vtkCountour->insertPoint(Point(p0Index, gridCell->v0.x, gridCell->v0.y, p_value));

			p1Index = pointIndex++;
			p_value = (((gridCell->v1.x * (gridCell->s2 - scalarValue)) + (gridCell->v2.x * (scalarValue - gridCell->s1))) / (gridCell->s2 - gridCell->s1));
			vtkCountour->insertPoint(Point(p1Index, p_value, gridCell->v1.y, gridCell->v1.z));

			p2Index = pointIndex++;
			p_value = (((gridCell->v1.y * (gridCell->s5 - scalarValue)) + (gridCell->v5.y * (scalarValue - gridCell->s1))) / (gridCell->s5 - gridCell->s1));
			vtkCountour->insertPoint(Point(p2Index, gridCell->v1.x, p_value, gridCell->v1.z));

			p3Index = pointIndex++;
			p_value = (((gridCell->v5.x * (gridCell->s6 - scalarValue)) + (gridCell->v6.x * (scalarValue - gridCell->s5))) / (gridCell->s6 - gridCell->s5));
			vtkCountour->insertPoint(Point(p3Index, p_value, gridCell->v5.y, gridCell->v5.z));

			p4Index = pointIndex++;
			p_value = (((gridCell->v6.z * (gridCell->s7 - scalarValue)) + (gridCell->v7.z * (scalarValue - gridCell->s6))) / (gridCell->s7 - gridCell->s6));
			vtkCountour->insertPoint(Point(p4Index, gridCell->v6.x, gridCell->v6.y, p_value));

			p5Index = pointIndex++;
			p_value = (((gridCell->v2.y * (gridCell->s6 - scalarValue)) + (gridCell->v6.y * (scalarValue - gridCell->s2))) / (gridCell->s6 - gridCell->s2));
			vtkCountour->insertPoint(Point(p5Index, gridCell->v2.x, p_value, gridCell->v2.z));

			p6Index = pointIndex++;
			p_value = (((gridCell->v4.z * (gridCell->s5 - scalarValue)) + (gridCell->v5.z * (scalarValue - gridCell->s4))) / (gridCell->s5 - gridCell->s4));
			vtkCountour->insertPoint(Point(p6Index, gridCell->v4.x, gridCell->v4.y, p_value));

			p7Index = pointIndex++;
			p_value = (((gridCell->v7.x * (gridCell->s4 - scalarValue)) + (gridCell->v4.x * (scalarValue - gridCell->s7))) / (gridCell->s4 - gridCell->s7));
			vtkCountour->insertPoint(Point(p7Index, p_value, gridCell->v7.y, gridCell->v7.z));

			p8Index = pointIndex++;
			p_value = (((gridCell->v0.y * (gridCell->s4 - scalarValue)) + (gridCell->v4.y * (scalarValue - gridCell->s0))) / (gridCell->s4 - gridCell->s0));
			vtkCountour->insertPoint(Point(p8Index, gridCell->v1.x, p_value, gridCell->v1.z));

			/*Polygon p0;

			p0.vertexIndexVect.push_back(p0Index);
			p0.vertexIndexVect.push_back(p1Index);
			p0.vertexIndexVect.push_back(p2Index);

			vtkCountour->insertPolygon(p0);

			Polygon p1;

			p1.vertexIndexVect.push_back(p3Index);
			p1.vertexIndexVect.push_back(p4Index);
			p1.vertexIndexVect.push_back(p5Index);

			vtkCountour->insertPolygon(p1);

			Polygon p2;

			p2.vertexIndexVect.push_back(p6Index);
			p2.vertexIndexVect.push_back(p7Index);
			p2.vertexIndexVect.push_back(p8Index);

			vtkCountour->insertPolygon(p2);*/
			break;
		}
		case 15: // 00001111
		{
			p0Index = pointIndex++;
			p_value = (((gridCell->v0.y * (gridCell->s4 - scalarValue)) + (gridCell->v4.y * (scalarValue - gridCell->s0))) / (gridCell->s4 - gridCell->s0));
			vtkCountour->insertPoint(Point(p0Index, gridCell->v1.x, p_value, gridCell->v1.z));

			p1Index = pointIndex++;
			p_value = (((gridCell->v1.y * (gridCell->s5 - scalarValue)) + (gridCell->v5.y * (scalarValue - gridCell->s1))) / (gridCell->s5 - gridCell->s1));
			vtkCountour->insertPoint(Point(p1Index, gridCell->v1.x, p_value, gridCell->v1.z));

			p2Index = pointIndex++;
			p_value = (((gridCell->v2.y * (gridCell->s6 - scalarValue)) + (gridCell->v6.y * (scalarValue - gridCell->s2))) / (gridCell->s6 - gridCell->s2));
			vtkCountour->insertPoint(Point(p2Index, gridCell->v2.x , p_value, gridCell->v2.z));

			p3Index = pointIndex++;
			p_value = (((gridCell->v3.y * (gridCell->s7 - scalarValue)) + (gridCell->v7.y * (scalarValue - gridCell->s3))) / (gridCell->s7 - gridCell->s3));
			vtkCountour->insertPoint(Point(p3Index, gridCell->v3.x, p_value, gridCell->v3.z));

			/*Polygon p;

			p.vertexIndexVect.push_back(p0Index);
			p.vertexIndexVect.push_back(p1Index);
			p.vertexIndexVect.push_back(p2Index);
			p.vertexIndexVect.push_back(p3Index);

			vtkCountour->insertPolygon(p);*/
			break;
		}
		case 141: // 10001101
		{
			p0Index = pointIndex++;
			p_value = (((gridCell->v0.z * (gridCell->s1 - scalarValue)) + (gridCell->v1.z * (scalarValue - gridCell->s0))) / (gridCell->s1 - gridCell->s0));
			vtkCountour->insertPoint(Point(p0Index, gridCell->v0.x, gridCell->v0.y, p_value));

			p1Index = pointIndex++;
			p_value = (((gridCell->v1.x * (gridCell->s2 - scalarValue)) + (gridCell->v2.x * (scalarValue - gridCell->s1))) / (gridCell->s2 - gridCell->s1));
			vtkCountour->insertPoint(Point(p1Index, p_value, gridCell->v1.y, gridCell->v1.z));

			p2Index = pointIndex++;
			p_value = (((gridCell->v2.y * (gridCell->s6 - scalarValue)) + (gridCell->v6.y * (scalarValue - gridCell->s2))) / (gridCell->s6 - gridCell->s2));
			vtkCountour->insertPoint(Point(p2Index, gridCell->v2.x, p_value, gridCell->v2.z));

			p3Index = pointIndex++;
			p_value = (((gridCell->v6.z * (gridCell->s7 - scalarValue)) + (gridCell->v7.z * (scalarValue - gridCell->s6))) / (gridCell->s7 - gridCell->s6));
			vtkCountour->insertPoint(Point(p3Index, gridCell->v6.x, gridCell->v6.y, p_value));

			p4Index = pointIndex++;
			p_value = (((gridCell->v7.x * (gridCell->s4 - scalarValue)) + (gridCell->v4.x * (scalarValue - gridCell->s7))) / (gridCell->s4 - gridCell->s7));
			vtkCountour->insertPoint(Point(p4Index, p_value, gridCell->v7.y, gridCell->v7.z));

			p5Index = pointIndex++;
			p_value = (((gridCell->v0.y * (gridCell->s4 - scalarValue)) + (gridCell->v4.y * (scalarValue - gridCell->s0))) / (gridCell->s4 - gridCell->s0));
			vtkCountour->insertPoint(Point(p5Index, gridCell->v1.x, p_value, gridCell->v1.z));

			/*Polygon p0;

			p0.vertexIndexVect.push_back(p0Index);
			p0.vertexIndexVect.push_back(p1Index);
			p0.vertexIndexVect.push_back(p2Index);
			p0.vertexIndexVect.push_back(p3Index);
			p0.vertexIndexVect.push_back(p4Index);
			p0.vertexIndexVect.push_back(p5Index);

			vtkCountour->insertPolygon(p0);*/
			break;
		}
		case 85: // 01010101
		{
			p0Index = pointIndex++;
			p_value = (((gridCell->v0.z * (gridCell->s1 - scalarValue)) + (gridCell->v1.z * (scalarValue - gridCell->s0))) / (gridCell->s1 - gridCell->s0));
			vtkCountour->insertPoint(Point(p0Index, gridCell->v0.x, gridCell->v0.y, p_value));

			p1Index = pointIndex++;
			p_value = (((gridCell->v4.z * (gridCell->s5 - scalarValue)) + (gridCell->v5.z * (scalarValue - gridCell->s4))) / (gridCell->s5 - gridCell->s4));
			vtkCountour->insertPoint(Point(p1Index, gridCell->v4.x, gridCell->v4.y, p_value));

			p2Index = pointIndex++;
			p_value = (((gridCell->v7.x * (gridCell->s4 - scalarValue)) + (gridCell->v4.x * (scalarValue - gridCell->s7))) / (gridCell->s4 - gridCell->s7));
			vtkCountour->insertPoint(Point(p2Index, p_value, gridCell->v7.y, gridCell->v7.z));

			p3Index = pointIndex++;
			p_value = (((gridCell->v3.x * (gridCell->s0 - scalarValue)) + (gridCell->v0.x * (scalarValue - gridCell->s3))) / (gridCell->s0 - gridCell->s3));
			vtkCountour->insertPoint(Point(p3Index, p_value, gridCell->v3.y, gridCell->v3.z));

			p4Index = pointIndex++;
			p_value = (((gridCell->v1.x * (gridCell->s2 - scalarValue)) + (gridCell->v2.x * (scalarValue - gridCell->s1))) / (gridCell->s2 - gridCell->s1));
			vtkCountour->insertPoint(Point(p4Index, p_value, gridCell->v1.y, gridCell->v1.z));

			p5Index = pointIndex++;
			p_value = (((gridCell->v5.x * (gridCell->s6 - scalarValue)) + (gridCell->v6.x * (scalarValue - gridCell->s5))) / (gridCell->s6 - gridCell->s5));
			vtkCountour->insertPoint(Point(p5Index, p_value, gridCell->v5.y, gridCell->v5.z));

			p6Index = pointIndex++;
			p_value = (((gridCell->v6.z * (gridCell->s7 - scalarValue)) + (gridCell->v7.z * (scalarValue - gridCell->s6))) / (gridCell->s7 - gridCell->s6));
			vtkCountour->insertPoint(Point(p6Index, gridCell->v6.x, gridCell->v6.y, p_value));

			p7Index = pointIndex++;
			p_value = (((gridCell->v2.z * (gridCell->s3 - scalarValue)) + (gridCell->v3.z * (scalarValue - gridCell->s2))) / (gridCell->s3 - gridCell->s2));
			vtkCountour->insertPoint(Point(p7Index, gridCell->v2.x, gridCell->v2.y, p_value));

			/*Polygon p0;

			p0.vertexIndexVect.push_back(p0Index);
			p0.vertexIndexVect.push_back(p1Index);
			p0.vertexIndexVect.push_back(p2Index);
			p0.vertexIndexVect.push_back(p3Index);

			vtkCountour->insertPolygon(p0);

			Polygon p1;
			
			p1.vertexIndexVect.push_back(p4Index);
			p1.vertexIndexVect.push_back(p5Index);
			p1.vertexIndexVect.push_back(p6Index);
			p1.vertexIndexVect.push_back(p7Index);

			vtkCountour->insertPolygon(p1);*/
			break;
		}
		case 77: // 01001101
		{
			p0Index = pointIndex++;
			p_value = (((gridCell->v0.z * (gridCell->s1 - scalarValue)) + (gridCell->v1.z * (scalarValue - gridCell->s0))) / (gridCell->s1 - gridCell->s0));
			vtkCountour->insertPoint(Point(p0Index, gridCell->v0.x, gridCell->v0.y, p_value));

			p1Index = pointIndex++;
			p_value = (((gridCell->v1.x * (gridCell->s2 - scalarValue)) + (gridCell->v2.x * (scalarValue - gridCell->s1))) / (gridCell->s2 - gridCell->s1));
			vtkCountour->insertPoint(Point(p1Index, p_value, gridCell->v1.y, gridCell->v1.z));

			p2Index = pointIndex++;
			p_value = (((gridCell->v5.x * (gridCell->s6 - scalarValue)) + (gridCell->v6.x * (scalarValue - gridCell->s5))) / (gridCell->s6 - gridCell->s5));
			vtkCountour->insertPoint(Point(p2Index, p_value, gridCell->v5.y, gridCell->v5.z));

			p3Index = pointIndex++;
			p_value = (((gridCell->v6.z * (gridCell->s7 - scalarValue)) + (gridCell->v7.z * (scalarValue - gridCell->s6))) / (gridCell->s7 - gridCell->s6));
			vtkCountour->insertPoint(Point(p3Index, gridCell->v6.x, gridCell->v6.y, p_value));

			p4Index = pointIndex++;
			p_value = (((gridCell->v0.y * (gridCell->s4 - scalarValue)) + (gridCell->v4.y * (scalarValue - gridCell->s0))) / (gridCell->s4 - gridCell->s0));
			vtkCountour->insertPoint(Point(p4Index, gridCell->v1.x, p_value, gridCell->v1.z));

			/*Polygon p0;

			p0.vertexIndexVect.push_back(p0Index);
			p0.vertexIndexVect.push_back(p1Index);
			p0.vertexIndexVect.push_back(p2Index);
			p0.vertexIndexVect.push_back(p3Index);
			p0.vertexIndexVect.push_back(p4Index);

			vtkCountour->insertPolygon(p0);*/
			break;
		}
		case 30: // 00011110
		{
			break;
		}
		case 165: // 10100101
		{
			p0Index = pointIndex++;
			p_value = (((gridCell->v5.x * (gridCell->s6 - scalarValue)) + (gridCell->v6.x * (scalarValue - gridCell->s5))) / (gridCell->s6 - gridCell->s5));
			vtkCountour->insertPoint(Point(p0Index, p_value, gridCell->v5.y, gridCell->v5.z));

			p1Index = pointIndex++;
			p_value = (((gridCell->v6.z * (gridCell->s7 - scalarValue)) + (gridCell->v7.z * (scalarValue - gridCell->s6))) / (gridCell->s7 - gridCell->s6));
			vtkCountour->insertPoint(Point(p1Index, gridCell->v6.x, gridCell->v6.y, p_value));

			p2Index = pointIndex++;
			p_value = (((gridCell->v2.y * (gridCell->s6 - scalarValue)) + (gridCell->v6.y * (scalarValue - gridCell->s2))) / (gridCell->s6 - gridCell->s2));
			vtkCountour->insertPoint(Point(p2Index, gridCell->v2.x, p_value, gridCell->v2.z));

			p3Index = pointIndex++;
			p_value = (((gridCell->v4.z * (gridCell->s5 - scalarValue)) + (gridCell->v5.z * (scalarValue - gridCell->s4))) / (gridCell->s5 - gridCell->s4));
			vtkCountour->insertPoint(Point(p3Index, gridCell->v4.x, gridCell->v4.y, p_value));

			p4Index = pointIndex++;
			p_value = (((gridCell->v7.x * (gridCell->s4 - scalarValue)) + (gridCell->v4.x * (scalarValue - gridCell->s7))) / (gridCell->s4 - gridCell->s7));
			vtkCountour->insertPoint(Point(p4Index, p_value, gridCell->v7.y, gridCell->v7.z));

			p5Index = pointIndex++;
			p_value = (((gridCell->v0.y * (gridCell->s4 - scalarValue)) + (gridCell->v4.y * (scalarValue - gridCell->s0))) / (gridCell->s4 - gridCell->s0));
			vtkCountour->insertPoint(Point(p5Index, gridCell->v1.x, p_value, gridCell->v1.z));
			break;
		}
		case 142: // 10001110
		{
			p0Index = pointIndex++;
			p_value = (((gridCell->v0.z * (gridCell->s1 - scalarValue)) + (gridCell->v1.z * (scalarValue - gridCell->s0))) / (gridCell->s1 - gridCell->s0));
			vtkCountour->insertPoint(Point(p0Index, gridCell->v0.x, gridCell->v0.y, p_value));

			p1Index = pointIndex++;
			p_value = (((gridCell->v1.y * (gridCell->s5 - scalarValue)) + (gridCell->v5.y * (scalarValue - gridCell->s1))) / (gridCell->s5 - gridCell->s1));
			vtkCountour->insertPoint(Point(p1Index, gridCell->v1.x, p_value, gridCell->v1.z));

			p2Index = pointIndex++;
			p_value = (((gridCell->v2.y * (gridCell->s6 - scalarValue)) + (gridCell->v6.y * (scalarValue - gridCell->s2))) / (gridCell->s6 - gridCell->s2));
			vtkCountour->insertPoint(Point(p2Index, gridCell->v2.x, p_value, gridCell->v2.z));

			p3Index = pointIndex++;
			p_value = (((gridCell->v6.z * (gridCell->s7 - scalarValue)) + (gridCell->v7.z * (scalarValue - gridCell->s6))) / (gridCell->s7 - gridCell->s6));
			vtkCountour->insertPoint(Point(p3Index, gridCell->v6.x, gridCell->v6.y, p_value));

			p4Index = pointIndex++;
			p_value = (((gridCell->v7.x * (gridCell->s4 - scalarValue)) + (gridCell->v4.x * (scalarValue - gridCell->s7))) / (gridCell->s4 - gridCell->s7));
			vtkCountour->insertPoint(Point(p4Index, p_value, gridCell->v7.y, gridCell->v7.z));

			p5Index = pointIndex++;
			p_value = (((gridCell->v3.x * (gridCell->s0 - scalarValue)) + (gridCell->v0.x * (scalarValue - gridCell->s3))) / (gridCell->s0 - gridCell->s3));
			vtkCountour->insertPoint(Point(p5Index, p_value, gridCell->v3.y, gridCell->v3.z));

			/*Polygon p0;

			p0.vertexIndexVect.push_back(p0Index);
			p0.vertexIndexVect.push_back(p1Index);
			p0.vertexIndexVect.push_back(p2Index);
			p0.vertexIndexVect.push_back(p3Index);
			p0.vertexIndexVect.push_back(p4Index);
			p0.vertexIndexVect.push_back(p5Index);

			vtkCountour->insertPolygon(p0);*/
			break;
		}
		default:
			break;
		}

		if ((i % 100) == 0)
		{
			std::cout << "[" << i << " / " << gridDomain->cellVector.size() << "]" << endl;
		}
	}

	std::cout << "Saving contour VTK file..." << endl;
	vtkCountour->saveVTK(outFilePath);
	std::cout << "Terminated!" << endl;

	return 0;
}