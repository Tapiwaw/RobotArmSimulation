#include "RawModel.h"

RawModel::RawModel()
	:m_ModelVertexBuffer(),m_TextureCoords(),m_ModelIndices(),m_ModelData()
{
	
}

RawModel::~RawModel()
{

}

void RawModel::Bind()
{
	m_ModelData.Bind();
	m_ModelIndices.Bind();
}

void RawModel::Unbind()
{
	m_ModelData.Unbind();
	m_ModelIndices.Unbind();
	m_ModelVertexBuffer.Unbind();
}

void RawModel::addVertexPositions(float * Positions, unsigned int Size)
{
	m_ModelVertexBuffer.AddData(Positions, Size);
	m_ModelData.AddVertexPosition(m_ModelVertexBuffer);
}

void RawModel::addTextureCoord(float * TextureCoords, unsigned int Size)
{
	m_TextureCoords.AddData(TextureCoords, Size);
	m_ModelData.AddVertexTextureCoords(m_TextureCoords);
}

void RawModel::addIndices(unsigned int * Indices, unsigned int Size)
{
	m_ModelIndices.AddData(Indices, Size);
}

unsigned int RawModel::GetIndicesCount()
{
	return m_ModelIndices.GetCount();
}
