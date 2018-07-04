#pragma once

#include <GL/glew.h>


#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "RawModel.h"


#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__ ))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer {
private:

public:
	Renderer();
	~Renderer();
	void Draw(const VertexArray& va, const IndexBuffer& ib, const ShaderProgram& program) const;
	void DrawRawModel(RawModel& Model, const ShaderProgram& program);
	void Clear() const;
};