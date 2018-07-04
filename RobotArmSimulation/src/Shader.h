#pragma once
#include <string>
#include <unordered_map>
#include "glm\glm.hpp"

class Shader {
private:
	std::string m_ShaderCode;
	std::string m_FilePath;
	unsigned int m_Type;
	unsigned int m_RendererID;

	static std::string readShaderFile(const std::string & filepath);
	static unsigned int CompileShader(unsigned int type, const std::string & source);
public:
	Shader(const std::string& filepath,unsigned int type);
	~Shader();

	inline unsigned int GetID() const { return m_RendererID; }
	inline unsigned int GetShaderType() const { return m_Type;  }
	inline const std::string GetShaderString() const { return m_ShaderCode; }

};


class ShaderProgram {
private:
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocationCache;
	int GetUniformLocation(const std::string& name);

public:
	ShaderProgram();
	~ShaderProgram();

	void Bind() const;
	void CompileAndLink() const;
	void Unbind() const;
	void AttachShader(Shader ShaderToAttatch);
	void DetachShader(Shader ShaderToDetach);
	inline unsigned int GetID() const { return m_RendererID; }

	/*Set Uniforms*/
	void SetUniform4f(const std::string& name, float V0, float V1, float V2, float V4);
	void SetUniformMat4f(const std::string& name, const glm::mat4 matrix);
	void SetUniform1i(const std::string& name, int value);
};