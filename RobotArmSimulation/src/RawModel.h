#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

class RawModel {

private:
	VertexBuffer m_ModelVertexBuffer;
	VertexBuffer m_TextureCoords;
	IndexBuffer m_ModelIndices;
	VertexArray m_ModelData;

	
public:
	RawModel();
	~RawModel();

	void Bind();
	void Unbind();

	void addVertexPositions(float *Positions, unsigned int Size);
	void addTextureCoord(float *TextureCoords, unsigned int Size);
	void addIndices(unsigned int *Indices, unsigned int Size);
	unsigned int GetIndicesCount();
};