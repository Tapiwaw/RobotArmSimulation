#pragma once
#include <iostream>
#include <string.h>
#include <vector>
#include <fstream>
#include <sstream>

class FileLoader
{
private:
	std::vector<std::vector<float>> m_VertexData;
	std::vector<std::vector<float>> m_TextureCoord;
	std::vector<std::vector<float>> m_Normal; 
	std::vector<unsigned int> m_Indices;

	std::vector<float> m_TextureCoordBuff;
	std::vector<float> m_NormalBuffer;

	unsigned int findNumVertices(const std::string& FileName);

public:
	FileLoader();
	~FileLoader();
	void load(const std::string& FileName, float *positionBuff, float *textureBuff, float *normalsBuff, unsigned int * indicesBuff);
	unsigned int GetVertexBufferSize(const std::string& FileName);
	unsigned int GetTextureBufferSize(const std::string& FileName);
	unsigned int GetNormalsBufferSize(const std::string& FileName);
	unsigned int GetIndexBufferSize(const std::string& FileName);
};

