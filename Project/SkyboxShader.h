#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GlobalTextureNumbers.h"

#include "Shader.h"

class SkyboxShader : public Shader
{
public:
	SkyboxShader();

	void SetShaderValues(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

	~SkyboxShader();

private:
	const char* vertexShaderLocation;
	const char* fragmentShaderLocation;

	GLuint shaderViewLocation, shaderProjectionLocation;
	GLuint shaderSkyboxTextureLocation;
};