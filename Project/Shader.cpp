#include "Shader.h"

Shader::Shader()
{
	// initialize shader ID
	shaderID = 0;
}

void Shader::CreateFromFiles(const char* vertexLocation, const char* fragmentLocation)
{
	// get the shader's code and convert them to a c-string
	std::string vertexString = ReadFile(vertexLocation);
	std::string fragmentString = ReadFile(fragmentLocation);
	const char* vertexCode = vertexString.c_str();
	const char* fragmentCode = fragmentString.c_str();

	// create a shader program using the vertex and fragment shader code
	BuildProgram(vertexCode, fragmentCode);
}

void Shader::CreateFromFiles(const char* vertexLocation, const char* geometryLocation, const char* fragmentLocation)
{
	// get the shader's code and convert them to a c-string
	std::string vertexString = ReadFile(vertexLocation);
	std::string geometryString = ReadFile(geometryLocation);
	std::string fragmentString = ReadFile(fragmentLocation);
	const char* vertexCode = vertexString.c_str();
	const char* geometryCode = geometryString.c_str();
	const char* fragmentCode = fragmentString.c_str();

	// create a shader program using the vertex and fragment shader code
	BuildProgram(vertexCode, geometryCode, fragmentCode);
}

std::string Shader::ReadFile(const char* fileLocation)
{
	// create a string to hold contents of file and open the file
	std::string content;
	std::ifstream fileStream(fileLocation, std::ios::in);

	// check if the file successfully opened
	if (!fileStream.is_open())
	{
		printf("Failed to read %s! File doesn't exist.", fileLocation);
		return "";
	}

	// get all the lines from the file and add them to the content string
	std::string line = "";
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	// close the file and return the content string
	fileStream.close();
	return content;
}

void Shader::ActivateShader()
{
	// use this shader
	glUseProgram(shaderID);
}

void Shader::DisableShader()
{
	// stop using this shader
	glUseProgram(0);
}

void Shader::ValidateProgram()
{
	// create an int to act as a bool value and create a cstring that is 1024 characters long to act as a log
	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	// validate the shader program to make sure it will run with how we have setup OpenGL, if it fails to validate
	// return the log of the shader program's validation status
	glValidateProgram(shaderID);
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error validating program: '%s'\n", eLog);
		return;
	}
}

void Shader::BuildProgram(const char* vertexCode, const char* fragmentCode)
{
	// create an empty shader program
	shaderID = glCreateProgram();

	// check if the shader program was created successfully and if it wasn't print an error message
	if (!shaderID)
	{
		printf("Error creating shader program!\n");
		return;
	}

	// add a vertex shader and fragment shader to the shader program
	AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
	AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

	// link the shader program
	CompileProgram();
}

void Shader::BuildProgram(const char* vertexCode, const char* geometryCode, const char* fragmentCode)
{
	// create an empty shader program
	shaderID = glCreateProgram();

	// check if the shader program was created successfully and if it wasn't print an error message
	if (!shaderID)
	{
		printf("Error creating shader program!\n");
		return;
	}

	// add the shaders to the shader program
	AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
	AddShader(shaderID, geometryCode, GL_GEOMETRY_SHADER);
	AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

	// link the shader program
	CompileProgram();
}

void Shader::AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
	// create an empty shader
	GLuint theShader = glCreateShader(shaderType);

	// create a c string which is the shader's source code
	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	// create a GLint which holds the number of characters that are in the shader's source code
	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	// attach the source code to the shader and compile it
	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	// create an int to act as a bool value and create a cstring that is 1024 characters long to act as a log
	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	// return a log of the shader's compile status if it failed to compile
	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		printf("Error compiling the %d shader: '%s'\n", shaderType, eLog);
		return;
	}

	// attach the shader to the shader program
	glAttachShader(theProgram, theShader);
}

void Shader::CompileProgram()
{
	// create an int to act as a bool value and create a cstring that is 1024 characters long to act as a log
	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	// link the shader program together and return it's linking status if it failed to link
	glLinkProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error linking program: '%s'\n", eLog);
		return;
	}
}

Shader::~Shader()
{
	// if we created a shader delete it
	if (shaderID != 0)
	{
		glDeleteProgram(shaderID);
	}
}