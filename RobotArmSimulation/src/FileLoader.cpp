#include "FileLoader.h"



unsigned int FileLoader::findNumVertices(const std::string & FileName)
{
	std::ifstream file;
	file.open(FileName);
	if (!file.is_open())
	{
		std::cout << "couldnt open file \" " << FileName << " \"" << std::endl;
		return 0;
	}
	std::string line;
	std::string token;
	unsigned int numberOfVertices = 0;
	while (std::getline(file, line)) {
		std::stringstream linestream(line); // for splitting vertex's, texture coords, normal coords
		if (std::getline(linestream, token, ' ')) {
			if (token == "v") {
				numberOfVertices++;
			}
			else if (token == "vt") {
				break;
			}
		}
	}
	file.close();
	return numberOfVertices;
}

FileLoader::FileLoader()
	:m_VertexData(), m_TextureCoord(), m_Normal(), m_Indices(),m_TextureCoordBuff(),m_NormalBuffer()
{
}


FileLoader::~FileLoader()
{

}
void FileLoader::load(const std::string& FileName, float *positionBuff, float *textureBuff, float *normalsBuff,unsigned int * indicesBuff)
{
	std::ifstream file;
	file.open(FileName);
	if (!file.is_open())
	{
		std::cout << "couldnt open file \" "<< FileName << " \"" << std::endl;
	}
	std::string line;
	std::string token;
	float tokenValue;
	int faceCount = 0;
	bool buffersCreated = false;

	while (std::getline(file, line)) //for every line in the file
	{
		//std::cout << line << std::endl;
		std::stringstream linestream(line); // for splitting vertex's, texture coords, normal coords
		std::stringstream vertexPointStream; // for splitting faces
		if (std::getline(linestream, token, ' ')) {
			//std::cout << token << std::endl;
			if (token == "v") 
			{
				std::vector<float> vectorCoord;
				/*Vertex X*/
				std::getline(linestream, token, ' ');
				tokenValue = ::atof(token.c_str());
				vectorCoord.push_back(tokenValue);
				/*Vertex Y*/
				std::getline(linestream, token, ' ');
				tokenValue = ::atof(token.c_str());
				vectorCoord.push_back(tokenValue);
				/*Vertex Z*/
				std::getline(linestream, token, ' ');
				tokenValue = ::atof(token.c_str());
				vectorCoord.push_back(tokenValue);

				m_VertexData.push_back(vectorCoord);
				//std::cout << "Vertex Found" << std::endl;
				//std::cout << " --X "<< vectorCoord[0] <<" --Y "<< vectorCoord[1] <<" --Z "<< vectorCoord[2] << std::endl;
			}else if (token == "vt"){


				std::vector<float> TextureCoord;
				/*Vertex U*/
				std::getline(linestream, token, ' ');
				tokenValue = ::atof(token.c_str());
				TextureCoord.push_back(tokenValue);
				/*Vertex V*/
				std::getline(linestream, token, ' ');
				tokenValue = ::atof(token.c_str());
				TextureCoord.push_back(tokenValue);

				m_TextureCoord.push_back(TextureCoord);
				//std::cout << "TextureCoord Found" << std::endl;
				//std::cout << " --U " << TextureCoord[0] << " --V " << TextureCoord[1] << std::endl;

			}else if (token == "vn") 
			{
				std::vector<float> NormalCoord;
				/*Vertex X*/
				std::getline(linestream, token, ' ');
				tokenValue = ::atof(token.c_str());
				NormalCoord.push_back(tokenValue);
				/*Vertex Y*/
				std::getline(linestream, token, ' ');
				tokenValue = ::atof(token.c_str());
				NormalCoord.push_back(tokenValue);
				/*Vertex Z*/
				std::getline(linestream, token, ' ');
				tokenValue = ::atof(token.c_str());
				NormalCoord.push_back(tokenValue);

				m_Normal.push_back(NormalCoord);
				//std::cout << "Normal Found" << std::endl;
				//std::cout << " --X " << NormalCoord[0] << " --Y " << NormalCoord[1] << " --Z " << NormalCoord[2] << std::endl;
			}
			else if (token == "f") {
				if (!buffersCreated) {
					m_TextureCoordBuff.resize(m_VertexData.size() * 2);
					m_NormalBuffer.resize(m_VertexData.size() * 3);
					buffersCreated = true;
				}
				std::string PartToken;
				int vertexIndex;
				int textureIndex;
				int normalIndex;
				// create indices buffer // load vertex,texture,Normal coordinates into a buffer
				faceCount++;
				for (int i = 0; i < 3; i++)
				{
					std::getline(linestream, token, ' ');
					vertexPointStream.str("");
					vertexPointStream.clear();
					vertexPointStream << token;
					/*Dealing with vertex positions*/
					std::getline(vertexPointStream, PartToken, '/');
					vertexIndex = ::atoi(PartToken.c_str());
					vertexIndex--; //indexing in file starts at 1 not 0;
					m_Indices.push_back(vertexIndex);

					/*Dealing with textures*/
					std::getline(vertexPointStream, PartToken, '/');
					textureIndex = ::atoi(PartToken.c_str());
					textureIndex--;  //indexing in file starts at 1 not 0;
					m_TextureCoordBuff[vertexIndex*2] = m_TextureCoord[textureIndex][0];
					m_TextureCoordBuff[vertexIndex*2 + 1] = m_TextureCoord[textureIndex][1]; // y coordinate has to be inverted

																							   /*Dealing with Normals*/
					std::getline(vertexPointStream, PartToken, '/');
					normalIndex = ::atoi(PartToken.c_str());
					normalIndex--;  //indexing in file starts at 1 not 0;
					for (int j = 0; j < 3; j++)
					{
						m_NormalBuffer[vertexIndex*3 + j] = m_Normal[normalIndex][j];
					}

					//std::cout << "vertexIndex = (" << vertexIndex << "), TextureIndex = (" << textureIndex << "), NormalIndex = (" << normalIndex << ")" << std::endl;
				}

			}


		}

	}
	//std::cout << " --VertexSize " << m_VertexData.size() << " --TextureSize " << m_TextureCoord.size() << " --NormalSize " << m_Normal.size() << " --NumFaces " << faceCount << " --Numindices " << m_Indices.size() << std::endl;
	
	/* Copy Data to arguments*/
	
	for (unsigned int i = 0; i < m_VertexData.size(); i++)
	{
		for (unsigned int j = 0; j < 3; j++)
		{
		//std::cout << "m_vertexData[" << i*3 + j<< "] = " << m_VertexData[i][j] << std::endl;
		positionBuff[i * 3 + j] = m_VertexData[i][j];
		}
	}
	
	for (unsigned int i = 0; i < m_VertexData.size() * 2; i++) {
		textureBuff[i] = m_TextureCoordBuff[i];
		//std::cout << "m_TextureBuff[" << i << "] = " << textureBuff[i] << std::endl;
	}
	for (unsigned int i = 0; i < m_VertexData.size() * 3; i++) {
		normalsBuff[i] = m_NormalBuffer[i];
		//std::cout << "m_normalsBuff[" << i << "] = " << normalsBuff[i] << std::endl;
	}
	for (unsigned int i = 0; i < m_Indices.size(); i++) {
		indicesBuff[i] = m_Indices[i];
		//std::cout << "m_Indices[" << i << "] = " << indicesBuff[i] << std::endl;
	}

	file.close();
}

unsigned int FileLoader::GetVertexBufferSize(const std::string & FileName)
{
	return findNumVertices(FileName)*3;
}

unsigned int FileLoader::GetTextureBufferSize(const std::string & FileName)
{
	return findNumVertices(FileName) *2;
}

unsigned int FileLoader::GetNormalsBufferSize(const std::string & FileName)
{
	return findNumVertices(FileName)*3;
}

unsigned int FileLoader::GetIndexBufferSize(const std::string & FileName)
{
	std::ifstream file;
	file.open(FileName);
	if (!file.is_open())
	{
		std::cout << "couldnt open file \" " << FileName << " \"" << std::endl;
		return 0;
	}
	std::string line;
	std::string token;
	unsigned int numberOfFaces = 0;
	while (std::getline(file, line)) {
		std::stringstream linestream(line); // for splitting vertex's, texture coords, normal coords
		if (std::getline(linestream, token, ' ')) {
			if (token == "f") {
				numberOfFaces++;
			}

		}
	}
	file.close();
	return numberOfFaces * 3;
}

