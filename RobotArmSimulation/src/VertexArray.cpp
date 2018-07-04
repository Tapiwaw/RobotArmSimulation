#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(const VertexBuffer & vb, const VertexBufferLayout & layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		/*Let openGL know the layout of the positions Array*/
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset)); // Discribe the format of the vertex attributes in the bound buffer
		offset += element.count* VertexBufferElement::GetSizeOfType(element.type);
	}

}

void VertexArray::AddVertexPosition(const VertexBuffer & vb)
{
	Bind();
	vb.Bind();
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0)); // Discribe the format of the vertex attributes in the bound buffer
	Unbind();
	vb.Unbind();
}

void VertexArray::AddVertexTextureCoords(const VertexBuffer & vb)
{
	Bind();
	vb.Bind();
	GLCall(glEnableVertexAttribArray(1));
	GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0)); // Discribe the format of the vertex attributes in the bound buffer
	Unbind();
	vb.Unbind();
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}
