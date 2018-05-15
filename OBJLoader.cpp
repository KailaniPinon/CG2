#include "ObjLoader.h"



namespace {
	//TODO: Take in file name instead of hardcoding a function
	//method belong to obj
	//function doesn't belong to obj
		//int ObjLoader::Load(std::string filePath, ObjData &data)
	int RecursiveLoad(const char *filePath, ObjLoader::ObjData &data)
	{

		std::ifstream file(filePath);
		std::string nextLine;

		while (std::getline(file, nextLine))
		{
			std::stringstream ss(nextLine);

			if (nextLine.length() > 2)
			{
				switch (nextLine[0])
				{
				case 'v':
					switch (nextLine[1])
					{
					case 32:
						if (data.vertices == nullptr)
						{
							++data.numVertices;
							continue;
						}

						for (int i = 0; i < 3; ++i)
						{
							float value = -1.0f;
							ss >> value;
							*data.vertices++ = value;
						}
						break;

					case 't':
						if (data.UVs == nullptr)
						{
							++data.numUVs;
							continue;
						}
						break;
					case 'n':
						if (data.normals == nullptr)
						{
							++data.numNormals;
							continue;
						}
						break;
					}
					break;
				case 'f':
					if (nextLine[1] ==32 && data.faces == nullptr)
					{
						++data.numFaces;
					}
					break;
				}
			}

		}
			//If faces != nullptr then we didn't set the faces, we just counted first. Run again.
			if (data.faces == nullptr) 
			{
				data.faces = (unsigned int*)malloc(data.numFaces * 3);
				data.vertices = (float*)malloc(data.numVertices * 3);
				data.normals = (float*)malloc(data.numNormals * 3);
				data.UVs = (float*)malloc(data.numUVs * 3);

				return RecursiveLoad(filePath, data);
			}
		return 0;
	}
}


int ObjLoader::Load(const char *filePath, ObjData &data)
	{
		return RecursiveLoad(filePath, data);
	}

