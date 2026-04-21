#pragma once

#include <vector>
#include <string>

#include <GLEW/include/glew.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "GlobalIncludes.h"
#include "GlobalTextureNumbers.h"

#include "Mesh.h"
#include "SkyboxShader.h"

class Skybox
{
public:
	Skybox();

	void DrawSkybox(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

	~Skybox();

private:
	std::vector<std::string> faceLocations;

	Mesh* skyboxMesh;
	SkyboxShader* skyboxShader;

	GLuint textureID;
};
