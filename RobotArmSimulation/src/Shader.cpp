#include "Shader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


#include "Renderer.h"


Shader::Shader(const std::string & filepath, unsigned int type)
	:m_FilePath(filepath), m_RendererID(0), m_Type(type)
{
	m_ShaderCode = readShaderFile(filepath);
	m_RendererID = CompileShader(type, m_ShaderCode);

}

Shader::~Shader()
{
}

std::string Shader::readShaderFile(const std::string& filepath) {
	std::ifstream stream(filepath);
	std::stringstream ss[1];
	std::string line;

	while (getline(stream, line)) {
		ss[0] << line << '\n';
	}

	return ss[0].str();
}


unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {

	GLCall(unsigned int id = glCreateShader(type));
	const char* src = source.c_str();
	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));

	/*Error Handling*/
	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE) {
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length * sizeof(char));
		GLCall(glGetShaderInfoLog(id, length, &length, message));
		std::cout << "Failed to Compile" << std::endl;
		std::cout << message << std::endl;
		GLCall(glDeleteShader(id));
		return 0;
	}
	return id;
}


ShaderProgram::ShaderProgram()
	:m_RendererID(0)
{
	GLCall(m_RendererID = glCreateProgram());
}

ShaderProgram::~ShaderProgram()
{
	GLCall(glUseProgram(0));
	GLCall(glDeleteProgram(m_RendererID));
}

void ShaderProgram::Bind() const
{
	GLCall(glUseProgram(m_RendererID));
}


void ShaderProgram::CompileAndLink() const
{
	GLCall(glLinkProgram(m_RendererID));
	GLCall(glValidateProgram(m_RendererID));
}

void ShaderProgram::Unbind() const
{
	GLCall(glUseProgram(0));
}

void ShaderProgram::AttachShader(Shader ShaderToAttatch)
{
	GLCall(glAttachShader(m_RendererID, ShaderToAttatch.GetID()));

}

void ShaderProgram::DetachShader(Shader ShaderToDetach)
{
	GLCall(glDetachShader(m_RendererID, ShaderToDetach.GetID()));
}

 int ShaderProgram::GetUniformLocation(const std::string & name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
	{
		return m_UniformLocationCache[name];
	}
	GLCall( int Location = glGetUniformLocation(m_RendererID, name.c_str()));
	//ASSERT(Location != -1);
	return Location;
}

void ShaderProgram::SetUniform4f(const std::string& name, float V0, float V1, float V2, float V3)
{
	GLCall(glUniform4f(GetUniformLocation(name), V0, V1, V2, V3));
}

void ShaderProgram::SetUniformMat4f(const std::string & name, const glm::mat4 matrix)
{
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

void ShaderProgram::SetUniform1i(const std::string& name, int value)
{
	GLCall(glUniform1i(GetUniformLocation(name), value));
}
