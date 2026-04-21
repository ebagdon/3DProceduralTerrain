#include "ChunkController.h"

ChunkController::ChunkController()
{
	// initialize shader
	terrainShader = new TerrainShader();

	// get the length of the chunk
	GLfloat firstVertPosX = chunkVertices[0];
	GLfloat secondVertPosX = chunkVertices[9];
	chunkLength = secondVertPosX - firstVertPosX;

	// initialize chunks
	chunkRenderDist = 10;
	chunk = new Mesh(chunkVertices, chunkIndices, 4, 36, 6);

	// initialize textures and material
	beachSandTexture = new Texture("Textures/Terrain/BeachSand.png");
	beachSandTexture->LoadTextureA();
	plainsGrassTexture = new Texture("Textures/Terrain/Plains_Grass.png");
	plainsGrassTexture->LoadTexture();
	plainsRockTexture = new Texture("Textures/Terrain/Plains_Rock.png");
	plainsRockTexture->LoadTexture();
	plainsSnowTexture = new Texture("Textures/Terrain/Plains_Snow.png");
	plainsSnowTexture->LoadTextureA();
	desertSandTexture = new Texture("Textures/Terrain/Desert_Sand.png");
	desertSandTexture->LoadTextureA();
	desertRockTexture = new Texture("Textures/Terrain/Desert_Rock.png");
	desertRockTexture->LoadTextureA();
	waterTexture = new Texture("Textures/Terrain/Water.png");
	waterTexture->LoadTexture();
	material = new Material(0.3f, 8.0f);

	// initialize noise
	noise = new Noise();

	// create the water mesh
	water = new Mesh(waterVertices, waterIndices, 4, 32, 6);
}

ChunkController::ChunkController(unsigned int chunkRenderDistance)
{
	// initialize shader
	terrainShader = new TerrainShader();

	// get the length of the chunk
	GLfloat firstVertPosX = chunkVertices[0];
	GLfloat secondVertPosX = chunkVertices[9];
	chunkLength = secondVertPosX - firstVertPosX;

	// initialize chunks
	chunkRenderDist = chunkRenderDistance;
	chunk = new Mesh(chunkVertices, chunkIndices, 4, 36, 6);

	// initialize textures and material
	beachSandTexture = new Texture("Textures/Terrain/BeachSand.png");
	beachSandTexture->LoadTextureA();
	plainsGrassTexture = new Texture("Textures/Terrain/Plains_Grass.png");
	plainsGrassTexture->LoadTexture();
	plainsRockTexture = new Texture("Textures/Terrain/Plains_Rock.png");
	plainsRockTexture->LoadTexture();
	plainsSnowTexture = new Texture("Textures/Terrain/Plains_Snow.png");
	plainsSnowTexture->LoadTextureA();
	desertSandTexture = new Texture("Textures/Terrain/Desert_Sand.png");
	desertSandTexture->LoadTextureA();
	desertRockTexture = new Texture("Textures/Terrain/Desert_Rock.png");
	desertRockTexture->LoadTextureA();
	waterTexture = new Texture("Textures/Terrain/Water.png");
	waterTexture->LoadTexture();
	material = new Material(0.3f, 8.0f);

	// initialize noise
	noise = new Noise(1.0f, 2.0f);

	// create the water mesh
	water = new Mesh(waterVertices, waterIndices, 4, 32, 6);
}

void ChunkController::DrawChunks(glm::mat4* viewMatrix, glm::mat4* projectionMatrix, glm::vec3 cameraPosition, DirectionalLight* directionalLight)
{
	// activate the terrain shader and initialize its common values
	terrainShader->ActivateShader();
	terrainShader->SetShaderCommonValues(*viewMatrix, *projectionMatrix, cameraPosition,
		true, directionalLight->GetColor(), directionalLight->GetAmbientIntensity(), directionalLight->GetDiffuseIntensity(), directionalLight->GetDirection(),
		material->GetSpecularIntensity(), material->GetShininess());

	// plains biome humidity threshold, anything below this humidity is a desert
	float minPlainsHumidityThreshold = 0.5f;

	// calculate terrain texture thresholds
	float minPlainsGrassHeightThreshold = noise->GetMaxHeightNoise() * 0.042f;
	float minPlainsRockHeightThreshold = noise->GetMaxHeightNoise() * 0.17f;
	float minPlainsSnowHeightThreshold = noise->GetMaxHeightNoise() * 0.24f;
	float minDesertSandHeightThreshold = noise->GetMaxHeightNoise() * 0.042f;
	float minDesertRockHeightThreshold = noise->GetMaxHeightNoise() * 0.21f;

	// go through every chunk and draw it
	for (int x = -chunkRenderDist; x <= chunkRenderDist; x++)
	{
		for (int z = -chunkRenderDist; z <= chunkRenderDist; z++)
		{
			// calculate the chunk's position
			int xSign = x > 0 ? 1 : -1;
			int zSign = z > 0 ? 1 : -1;
			GLfloat chunkPosX = x != 0 ? (x * chunkLength) - ((chunkLength / 2) * xSign) : 0.0f;
			chunkPosX += cameraPosition.x;
			GLfloat chunkPosZ = z != 0 ? (z * chunkLength) - ((chunkLength / 2) * zSign) : 0.0f;
			chunkPosZ += cameraPosition.z;

			// calculate the noise values for each vertice of the chunk
			float frontLeftVertHeightNoise = noise->GetHeightNoise(chunkPosX - (chunkLength / 2), chunkPosZ + (chunkLength / 2));
			float frontRightVertHeightNoise = noise->GetHeightNoise(chunkPosX + (chunkLength / 2), chunkPosZ + (chunkLength / 2));
			float backRightVertHeightNoise = noise->GetHeightNoise(chunkPosX + (chunkLength / 2), chunkPosZ - (chunkLength / 2));
			float backLeftVertHeightNoise = noise->GetHeightNoise(chunkPosX - (chunkLength / 2), chunkPosZ - (chunkLength / 2));

			// calculate the position of each vertex
			glm::vec3 frontLeftVertPos = glm::vec3(chunkPosX - (chunkLength / 2), frontLeftVertHeightNoise, chunkPosZ + (chunkLength / 2));
			glm::vec3 frontRightVertPos = glm::vec3(chunkPosX + (chunkLength / 2), frontRightVertHeightNoise, chunkPosZ + (chunkLength / 2));
			glm::vec3 backRightVertPos = glm::vec3(chunkPosX + (chunkLength / 2), backRightVertHeightNoise, chunkPosZ - (chunkLength / 2));
			glm::vec3 backLeftVertPos = glm::vec3(chunkPosX - (chunkLength / 2), backLeftVertHeightNoise, chunkPosZ - (chunkLength / 2));
				
			// calculate the humidity noise value of each vertex
			float frontLeftVertHumidityNoise = noise->GetHumidityNoise(frontLeftVertPos.x, frontLeftVertPos.z);
			float frontRightVertHumidityNoise = noise->GetHumidityNoise(frontRightVertPos.x, frontRightVertPos.z);
			float backRightVertHumidityNoise = noise->GetHumidityNoise(backRightVertPos.x, backRightVertPos.z);
			float backLeftVertHumidityNoise = noise->GetHumidityNoise(backLeftVertPos.x, backLeftVertPos.z);

			// calculate a model matrix to apply to each of the chunk's vertices
			glm::mat4 frontLeftVertModelMatrix = glm::mat4(1.0f);
			frontLeftVertModelMatrix = glm::translate(frontLeftVertModelMatrix, glm::vec3(chunkPosX, frontLeftVertHeightNoise, chunkPosZ));
			glm::mat4 frontRightVertModelMatrix = glm::mat4(1.0f);
			frontRightVertModelMatrix = glm::translate(frontRightVertModelMatrix, glm::vec3(chunkPosX, frontRightVertHeightNoise, chunkPosZ));
			glm::mat4 backRightVertModelMatrix = glm::mat4(1.0f);
			backRightVertModelMatrix = glm::translate(backRightVertModelMatrix, glm::vec3(chunkPosX, backRightVertHeightNoise, chunkPosZ));
			glm::mat4 backLeftVertModelMatrix = glm::mat4(1.0f);
			backLeftVertModelMatrix = glm::translate(backLeftVertModelMatrix, glm::vec3(chunkPosX, backLeftVertHeightNoise, chunkPosZ));

			// bind textures to a texture unit
			beachSandTexture->UseTexture(BEACH_SAND_TEXTURE_UNIT);
			plainsGrassTexture->UseTexture(PLAINS_GRASS_TEXTURE_UNIT);
			plainsRockTexture->UseTexture(PLAINS_ROCK_TEXTURE_UNIT);
			plainsSnowTexture->UseTexture(PLAINS_SNOW_TEXTURE_UNIT);
			desertSandTexture->UseTexture(DESERT_SAND_TEXTURE_UNIT);
			desertRockTexture->UseTexture(DESERT_ROCK_TEXTURE_UNIT);

			// calculate the chunk's normals, set the shader's terrain related variables, and draw the chunk
			chunk->SetHumidityNoiseValues(chunkVertices, 4, 36, frontLeftVertHumidityNoise, frontRightVertHumidityNoise, backRightVertHumidityNoise, backLeftVertHumidityNoise);
			chunk->CalculateNormals(chunkVertices, 4, 36, frontLeftVertPos, frontRightVertPos, backRightVertPos, backLeftVertPos);
			terrainShader->SetShaderTerrainValues(frontLeftVertModelMatrix, frontRightVertModelMatrix, backRightVertModelMatrix, backLeftVertModelMatrix,
				minPlainsHumidityThreshold,
				minPlainsGrassHeightThreshold, minPlainsRockHeightThreshold, minPlainsSnowHeightThreshold,
				minDesertSandHeightThreshold, minDesertRockHeightThreshold);
			chunk->Draw(6);
		}
	}

	// the water level on the terrain
	float waterLevel = noise->GetMaxHeightNoise() * 0.036f;

	// calculate the water's model matrix
	glm::mat4 waterModelMatrix = glm::mat4(1.0f);
	waterModelMatrix = glm::translate(waterModelMatrix, glm::vec3(cameraPosition.x, waterLevel, cameraPosition.z));
	waterModelMatrix = glm::scale(waterModelMatrix, glm::vec3(chunkRenderDist + chunkRenderDist + 1.0f, 0.0f, chunkRenderDist + chunkRenderDist + 1.0f));

	// give the terrain shader the water model matrix
	terrainShader->SetShaderWaterValues(waterModelMatrix);

	// draw the water
	waterTexture->UseTexture(WATER_TEXTURE_UNIT);
	water->Draw(6);
	
	// disable the shader
	terrainShader->DisableShader();
}

ChunkController::~ChunkController()
{

}