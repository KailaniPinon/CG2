#pragma once
//#include "Init.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

//TODO: make function to clean up model data

namespace ObjLoader
{
	struct ObjData
	{
		float *vertices = nullptr;
		float *normals = nullptr;
		float *UVs = nullptr;
		unsigned int *faces = nullptr;		
		unsigned int numVertices = 0, numFaces = 0, numNormals = 0, numUVs = 0;
	};

	int Load(const char *filePath, ObjData &data);

	//int RecursiveLoad(const char *filePath, ObjData &data, int numInterations = 0);
}