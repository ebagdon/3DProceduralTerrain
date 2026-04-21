#pragma once

#include <fstream>
#include <string>

#include <GLEW/include/glew.h>

class Shader
{
public:
	Shader();

	void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);
	void CreateFromFiles(const char* vertexLocation, const char* geometryLocation, const char* fragmentLocation);
	std::string ReadFile(const char* fileLocation);

	void ActivateShader();
	void DisableShader();

	void ValidateProgram();

	~Shader();

protected:
	GLuint shaderID;

	void BuildProgram(const char* vertexCode, const char* fragmentCode);
	void BuildProgram(const char* vertexCode, const char* geometryCode, const char* fragmentCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
	void CompileProgram();
};