#include "IndexBuffer.h"
#include "Renderer.h"

IndexBuffer::IndexBuffer()
	:m_Count(0)
{
	GLCall(glGenBuffers(1, &m_RendererID)); // Generate one buffer & put buffer ID into buffer
}

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
	:m_Count(count)
{
	ASSERT(sizeof(unsigned int) == sizeof(GLuint));

	GLCall(glGenBuffers(1, &m_RendererID)); // Generate one buffer & put buffer ID into buffer
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID)); // tell opengl I want to work on this buffer
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW)); // Load data into vertex buffer
}

IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::AddData(const unsigned int * data, unsigned int count)
{
	ASSERT(sizeof(unsigned int) == sizeof(GLuint));
	m_Count = count;
	Bind();
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW)); // Load data into vertex buffer
	Unbind();
}

void IndexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID)); // tell opengl I want to work on this buffer
}

void IndexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0)); // tell opengl I want to work on this buffer
}
