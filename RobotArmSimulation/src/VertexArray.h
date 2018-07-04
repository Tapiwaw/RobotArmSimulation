#pragma once

#include "VertexBuffer.h"

class VertexBufferLayout;

class VertexArray
{
private:
	unsigned int m_RendererID;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void AddVertexPosition(const VertexBuffer& vb);
	void AddVertexTextureCoords(const VertexBuffer& vb);

	void Bind() const;
	void Unbind() const;
};