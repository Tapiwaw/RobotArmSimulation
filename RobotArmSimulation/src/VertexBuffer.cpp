#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer()
{
	GLCall(glGenBuffers(1, &m_RendererID)); // Generate one buffer & put buffer ID into buffer
}
VertexBuffer::VertexBuffer(const void * data, unsigned int size)
{
	GLCall(glGenBuffers(1, &m_RendererID)); // Generate one buffer & put buffer ID into buffer
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID)); // tell opengl I want to work on this buffer
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW)); // Load data into vertex buffer
}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::AddData(const void * data, unsigned int size)
{
	Bind();
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW)); // Load data into vertex buffer
	Unbind();
}

void VertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID)); // tell opengl I want to work on this buffer
}

void VertexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0)); // tell opengl I want to work on this buffer
}
