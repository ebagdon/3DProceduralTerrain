#pragma once

#include <vector>
#include <cmath>

#include <glm/glm.hpp>

#include "GlobalTextureNumbers.h"

#include "TerrainShader.h"
#include "DirectionalLight.h"
#include "Mesh.h"
#include "Texture.h"
#include "Material.h"
#include "Noise.h"

class ChunkController
{
public:
	ChunkController();
	ChunkController(unsigned int chunkRenderDistance);

	void DrawChunks(glm::mat4* viewMatrix, glm::mat4* projectionMatrix, glm::vec3 cameraPosition, DirectionalLight* directionalLight);

	~ChunkController();

private:
	GLfloat chunkVertices[36] = {
		-0.10f, 0.0f, 0.10f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f,	0.0f,
		0.10f, 0.0f, 0.10f,			1.0f, 0.0f,		0.0f, 1.0f, 0.0f,	0.0f,
		0.10f, 0.0f, -0.10f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,	0.0f,
		-0.10f, 0.0f, -0.10f,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f,	0.0f
	};

	unsigned int chunkIndices[6] = {
		1, 2, 3,
		3, 0, 1
	};

	TerrainShader* terrainShader;

	Mesh* chunk;
	GLfloat chunkLength;
	int chunkRenderDist;

	Texture* beachSandTexture;
	Texture* plainsGrassTexture;
	Texture* plainsRockTexture;
	Texture* plainsSnowTexture;
	Texture* desertSandTexture;
	Texture* desertRockTexture;
	Texture* waterTexture;
	Material* material;

	Noise* noise;

	GLfloat waterVertices[32] = {
		-0.10f, 0.0f, 0.10f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
		0.10f, 0.0f, 0.10f,			1.0f, 0.0f,		0.0f, 1.0f, 0.0f,
		0.10f, 0.0f, -0.10f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
		-0.10f, 0.0f, -0.10f,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f
	};

	unsigned int waterIndices[6] = {
		1, 2, 3,
		3, 0, 1
	};

	Mesh* water;
};