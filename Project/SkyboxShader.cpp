#include "SkyboxShader.h"

SkyboxShader::SkyboxShader()
{
	// create a shader from the given file locations
	vertexShaderLocation = "Shaders/skyboxshader.vert";
	fragmentShaderLocation = "Shaders/skyboxshader.frag";
	CreateFromFiles(vertexShaderLocation, fragmentShaderLocation);

	// get shader variable locations
	shaderViewLocation = glGetUniformLocation(shaderID, "view");
	shaderProjectionLocation = glGetUniformLocation(shaderID, "projection");

	shaderSkyboxTextureLocation = glGetUniformLocation(shaderID, "skyboxTexture");
}

void SkyboxShader::SetShaderValues(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
	// set shader variables
	glUniformMatrix4fv(shaderViewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(shaderProjectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	glUniform1i(shaderSkyboxTextureLocation, SHADER_SKYBOX_TEXTURE_UNIT);
}

SkyboxShader::~SkyboxShader()
{

}