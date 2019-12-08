#include "VTKFile.h"

using namespace MarchingCubes;

vector<string> VTKFile::tokenizer(const string& p_pcstStr, char delim)
{
	vector<string> tokens;
	stringstream strStream(p_pcstStr);
	string tmpString;

	while (getline(strStream, tmpString, delim))
	{
		tokens.push_back(tmpString);
	}

	return tokens;
}

VTKFile* VTKFile::loadFile(string filePath)
{
	// Abre o arquivo
	ifstream vtkFileStream(filePath.c_str());

	// Verifica se o arquivo foi aberto
	if (!vtkFileStream.is_open())
	{
		LogHelper::log("VTKFileException", "O arquivo VTK não pôde ser aberto");
	}
	else
	{
		// Arquivo VTK
		VTKFile *vtkFile = new VTKFile();

		// Variáveis auxiliares
		bool isValidGrid = false;
		string lineRead, strTrash;

		// Lê todo o arquivo linha por linha
		while (getline(vtkFileStream, lineRead))
		{
			if (!lineRead.empty())
			{
				if (!isValidGrid && ((lineRead.find("STRUCTURED_GRID") != string::npos) || (lineRead.find("STRUCTURED_POINTS") != string::npos)))
				{
					isValidGrid = true;
				}
				else if (isValidGrid)
				{
					if (lineRead.find("DIMENSIONS") != string::npos)
					{
						istringstream strStream(lineRead);
						strStream >> strTrash >> vtkFile->dimension.xDim >> vtkFile->dimension.yDim >> vtkFile->dimension.zDim;
					}

					if (lineRead.find("ORIGIN") != string::npos)
					{
						istringstream strStream(lineRead);
						strStream >> strTrash >> vtkFile->originPoint.x >> vtkFile->originPoint.y >> vtkFile->originPoint.z;
					}

					if (lineRead.find("SPACING") != string::npos)
					{
						istringstream strStream(lineRead);
						strStream >> strTrash >> vtkFile->spacing.xSpacing >> vtkFile->spacing.ySpacing >> vtkFile->spacing.zSpacing;
					}

					if (lineRead.find("POINTS") != string::npos)
					{
						istringstream strStream1(lineRead);

						int numPoint;
						strStream1 >> strTrash >> numPoint >> strTrash;

						float xPoint, yPoint, zPoint;

						for (int i = 0; i < numPoint; i++)
						{
							getline(vtkFileStream, lineRead);

							if (!lineRead.empty())
							{
								istringstream strStream2(lineRead);
								strStream2 >> xPoint >> yPoint >> zPoint;

								vtkFile->pointVector.push_back(Point(i, xPoint, yPoint, zPoint));
							}
						}
					}

					if (lineRead.find("POINT_DATA") != string::npos)
					{
						istringstream strStream(lineRead);
						strStream >> strTrash >> vtkFile->pointDataCount;
					}

					if (lineRead.find("SCALARS") != string::npos)
					{
						getline(vtkFileStream, strTrash);

						int readCount = 0;
						float scalarValue;

						while (readCount < vtkFile->pointDataCount)
						{
							getline(vtkFileStream, lineRead);

							if (!lineRead.empty())
							{
								vector<string> lineTokens = tokenizer(lineRead, ' ');

								for (int i = 0; i < lineTokens.size(); i++)
								{
									istringstream strStream(lineTokens.at(i));
									strStream >> scalarValue;

									vtkFile->scalarVector.push_back(scalarValue);
									readCount++;
								}
							}
						}
					}
				}
			}
		}

		vtkFileStream.close();

		if (vtkFile->pointVector.size() == 0)
		{
			int pointIndex = 0;

			for (int k = 0; k < vtkFile->dimension.zDim; k += vtkFile->spacing.zSpacing)
			{
				for (int j = 0; j < vtkFile->dimension.yDim; j += vtkFile->spacing.ySpacing)
				{
					for (int i = 0; i < vtkFile->dimension.xDim; i += vtkFile->spacing.xSpacing)
					{
						vtkFile->pointVector.push_back(Point(pointIndex++, i, j, k));
					}
				}
			}
		}

		return vtkFile;
	}

	return NULL;
}

GridDomain* VTKFile::toGridDomain()
{
	GridDomain *gridDomain = new GridDomain();

	int id0, id1, id2, id3, id4, id5, id6, id7;
	float s0, s1, s2, s3, s4, s5, s6, s7;

	int cellId = 0;

	int xIndexDisp0 = 0;
	int zIndexDisp0 = (this->dimension.xDim * this->dimension.yDim);

	int xIndexDisp1 = this->dimension.xDim;
	int zIndexDisp1 = ((this->dimension.xDim * this->dimension.yDim) + this->dimension.xDim);

	int totalIndexCount = 1790192;
	int indexCount = 0;

	while (indexCount < totalIndexCount)
	{
		id0 = xIndexDisp0;
		id1 = zIndexDisp0;
		id2 = (id1 + 1);
		id3 = (id0 + 1);

		id4 = xIndexDisp1;
		id5 = zIndexDisp1;
		id6 = (id4 + 1);
		id7 = (id5 + 1);

		Point p0(id0, this->pointVector[id0].x, this->pointVector[id0].y, this->pointVector[id0].z);
		Point p1(id1, this->pointVector[id1].x, this->pointVector[id1].y, this->pointVector[id1].z);
		Point p2(id2, this->pointVector[id2].x, this->pointVector[id2].y, this->pointVector[id2].z);
		Point p3(id3, this->pointVector[id3].x, this->pointVector[id3].y, this->pointVector[id3].z);
		Point p4(id4, this->pointVector[id4].x, this->pointVector[id4].y, this->pointVector[id4].z);
		Point p5(id5, this->pointVector[id5].x, this->pointVector[id5].y, this->pointVector[id5].z);
		Point p6(id6, this->pointVector[id6].x, this->pointVector[id6].y, this->pointVector[id6].z);
		Point p7(id7, this->pointVector[id7].x, this->pointVector[id7].y, this->pointVector[id7].z);

		s0 = this->scalarVector[id0];
		s1 = this->scalarVector[id1];
		s2 = this->scalarVector[id2];
		s3 = this->scalarVector[id3];
		s4 = this->scalarVector[id4];
		s5 = this->scalarVector[id5];
		s6 = this->scalarVector[id6];
		s7 = this->scalarVector[id7];

		GridCell cell;

		cell.id = cellId++;

		cell.v0 = p0;
		cell.v1 = p1;
		cell.v2 = p2;
		cell.v3 = p3;
		cell.v4 = p4;
		cell.v5 = p5;
		cell.v6 = p6;
		cell.v7 = p7;

		cell.s0 = s0;
		cell.s1 = s1;
		cell.s2 = s2;
		cell.s3 = s3;
		cell.s4 = s4;
		cell.s5 = s5;
		cell.s6 = s6;
		cell.s7 = s7;

		gridDomain->cellVector.push_back(cell);

		
		if ((xIndexDisp0 != 0) && (((xIndexDisp0 + 2) % (this->dimension.xDim * this->dimension.yDim - this->dimension.xDim)) == 0))
		{
			xIndexDisp0 += (this->dimension.xDim + 2);
			zIndexDisp0 += (this->dimension.xDim + 2);

			xIndexDisp1 += (this->dimension.xDim + 2);
			zIndexDisp1 += (this->dimension.xDim + 2);
		}
		else if ((xIndexDisp0 != 0) && (((xIndexDisp0 + 2) % this->dimension.xDim) == 0))
		{
			xIndexDisp0 += 2;
			zIndexDisp0 += 2;

			xIndexDisp1 += 2;
			zIndexDisp1 += 2;
		}
		else
		{
			xIndexDisp0++;
			zIndexDisp0++;

			xIndexDisp1++;
			zIndexDisp1++;
		}

		indexCount++;
	}

	return gridDomain;
}

void VTKFile::saveVTK(string filePath)
{
	// Abrindo o arquivo informado
	ofstream vtkFileStream(filePath.c_str());

	// Verifica se o arquivo foi aberto
	if (!vtkFileStream.is_open())
	{
		LogHelper::log("VTKFileException", "O arquivo VTK não pôde ser criado");
	}
	else
	{
		vtkFileStream << std::fixed << std::setprecision(7);

		// Cabeçalho do arquivo VTK
		vtkFileStream << "# vtk DataFile Version 3.0" << endl;
		vtkFileStream << "vtk output" << endl;
		vtkFileStream << "ASCII" << endl;
		vtkFileStream << "DATASET POLYDATA" << endl;

		if (this->pointVector.size() > 0)
		{
			vtkFileStream << "POINTS  " << this->pointVector.size() << "  float" << endl;

			// Pontos no arquivo VTK
			for (int i = 0; i < this->pointVector.size(); i++)
			{
				vtkFileStream << this->pointVector[i].x << "  " << this->pointVector[i].y << "  " << this->pointVector[i].z << endl;
			}
		}

		if (this->lineVector.size() > 0)
		{
			vtkFileStream << "LINES  " << this->lineVector.size() << "  " << (3 * this->lineVector.size()) << endl;

			// Linhas no arquivo VTK
			for (int i = 0; i < this->lineVector.size(); i++)
			{
				vtkFileStream << "2  " << this->lineVector[i].startPointIndex << "  " << this->lineVector[i].endPointIndex << endl;
			}
		}

		if (this->polygonVector.size() > 0)
		{
			vtkFileStream << "POLYGONS  " << this->polygonVector.size() << "  " << this->polygonDataCount << endl;

			for (int i = 0; i < this->polygonVector.size(); i++)
			{
				vtkFileStream << this->polygonVector[i].vertexIndexVect.size();

				for (int j = 0; j < this->polygonVector[i].vertexIndexVect.size(); j++)
				{
					vtkFileStream << "  " << this->polygonVector[i].vertexIndexVect[j];
				}

				vtkFileStream << endl;
			}
		}

		if (this->scalarVector.size() > 0)
		{
			vtkFileStream << "POINT_DATA  " << this->scalarVector.size() << endl;
			vtkFileStream << "SCALARS scalar_value float" << endl;
			vtkFileStream << "LOOKUP_TABLE default" << endl;

			// Linhas no arquivo VTK
			for (int i = 0; i < this->scalarVector.size(); i++)
			{
				vtkFileStream << this->scalarVector[i] << endl;
			}
		}



		vtkFileStream.close();
	}
}

void VTKFile::insertPoint(Point &point)
{
	this->pointVector.push_back(point);
}

void VTKFile::insertLine(Line &line)
{
	this->lineVector.push_back(line);
}

void VTKFile::insertPolygon(Polygon &p)
{
	this->polygonVector.push_back(p);
	this->polygonDataCount += (p.vertexIndexVect.size() + 1);
}