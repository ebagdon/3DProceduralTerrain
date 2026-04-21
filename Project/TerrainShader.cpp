#include "TerrainShader.h"

TerrainShader::TerrainShader() : Shader()
{
	// create a shader from the given file locations
	vertexShaderLocation = "Shaders/terrainshader.vert";
	geometryShaderLocation = "Shaders/terrainshader.geom";
	fragmentShaderLocation = "Shaders/terrainshader.frag";
	CreateFromFiles(vertexShaderLocation, geometryShaderLocation, fragmentShaderLocation);

	// get locations of shader variables
	shaderViewLocation = glGetUniformLocation(shaderID, "view");
	shaderProjectionLocation = glGetUniformLocation(shaderID, "projection");
	shaderCameraPositionLocation = glGetUniformLocation(shaderID, "cameraPosition");

	shaderDirectionalLightInUseLocation = glGetUniformLocation(shaderID, "directionalLight.inUse");
	shaderDirectionalLightColorLocation = glGetUniformLocation(shaderID, "directionalLight.base.color");
	shaderDirectionalLightAmbientIntensityLocation = glGetUniformLocation(shaderID, "directionalLight.base.ambientIntensity");
	shaderDirectionalLightDiffuseIntensityLocation = glGetUniformLocation(shaderID, "directionalLight.base.diffuseIntensity");
	shaderDirectionalLightDirectionLocation = glGetUniformLocation(shaderID, "directionalLight.direction");
	shaderSpecularIntensityLocation = glGetUniformLocation(shaderID, "material.specularIntensity");
	shaderShininessLocation = glGetUniformLocation(shaderID, "material.shininess");

	shaderIsGeomTerrainLocation = glGetUniformLocation(shaderID, "isGeomTerrain");
	shaderIsFragTerrainLocation = glGetUniformLocation(shaderID, "isFragTerrain");

	shaderFrontLeftVertModelMatrixLocation = glGetUniformLocation(shaderID, "frontLeftVertModelMatrix");
	shaderFrontRightVertModelMatrixLocation = glGetUniformLocation(shaderID, "frontRightVertModelMatrix");
	shaderBackRightVertModelMatrixLocation = glGetUniformLocation(shaderID, "backRightVertModelMatrix");
	shaderBackLeftVertModelMatrixLocation = glGetUniformLocation(shaderID, "backLeftVertModelMatrix");

	shaderWaterModelMatrixLocation = glGetUniformLocation(shaderID, "waterModelMatrix");

	shaderBeachSandTextureLocation = glGetUniformLocation(shaderID, "beachSandTexture");
	shaderPlainsGrassTextureLocation = glGetUniformLocation(shaderID, "plainsGrassTexture");
	shaderPlainsRockTextureLocation = glGetUniformLocation(shaderID, "plainsRockTexture");
	shaderPlainsSnowTextureLocation = glGetUniformLocation(shaderID, "plainsSnowTexture");
	shaderDesertSandTextureLocation = glGetUniformLocation(shaderID, "desertSandTexture");
	shaderDesertRockTextureLocation = glGetUniformLocation(shaderID, "desertRockTexture");
	shaderWaterTextureLocation = glGetUniformLocation(shaderID, "waterTexture");

	shaderMinPlainsHumidityThresholdLocation = glGetUniformLocation(shaderID, "minPlainsHumidityThreshold");

	shaderMinPlainsGrassHeightThresholdLocation = glGetUniformLocation(shaderID, "minPlainsGrassHeightThreshold");
	shaderMinPlainsRockHeightThresholdLocation = glGetUniformLocation(shaderID, "minPlainsRockHeightThreshold");
	shaderMinPlainsSnowHeightThresholdLocation = glGetUniformLocation(shaderID, "minPlainsSnowHeightThreshold");
	shaderMinDesertSandHeightThresholdLocation = glGetUniformLocation(shaderID, "minDesertSandHeightThreshold");
	shaderMinDesertRockHeightThresholdLocation = glGetUniformLocation(shaderID, "minDesertRockHeightThreshold");
}

void TerrainShader::SetShaderCommonValues(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 cameraPosition,
	bool directionalLightInUse, glm::vec3 directionalLightColor,
	float directionalLightAmbientIntensity, float directionalLightDiffuseIntensity, glm::vec3 directionalLightDirection,
	float specularIntensity, float shininess)
{
	// set values of common shader variables
	glUniformMatrix4fv(shaderViewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(shaderProjectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniform3f(shaderCameraPositionLocation, cameraPosition.x, cameraPosition.y, cameraPosition.z);

	glUniform1i(shaderDirectionalLightInUseLocation, directionalLightInUse);
	glUniform3f(shaderDirectionalLightColorLocation, directionalLightColor.x, directionalLightColor.y, directionalLightColor.z);
	glUniform1f(shaderDirectionalLightAmbientIntensityLocation, directionalLightAmbientIntensity);
	glUniform1f(shaderDirectionalLightDiffuseIntensityLocation, directionalLightDiffuseIntensity);
	glUniform3f(shaderDirectionalLightDirectionLocation, directionalLightDirection.x, directionalLightDirection.y, directionalLightDirection.z);
	glUniform1f(shaderSpecularIntensityLocation, specularIntensity);
	glUniform1f(shaderShininessLocation, shininess);
}

void TerrainShader::SetShaderTerrainValues(glm::mat4 frontLeftVertModelMatrix, glm::mat4 frontRightVertModelMatrix, glm::mat4 backRightVertModelMatrix, glm::mat4 backLeftVertModelMatrix,
	float minPlainsHumidityThreshold,
	float minPlainsGrassHeightThreshold, float minPlainsRockHeightThreshold, float minPlainsSnowHeightThreshold,
	float minDesertSandHeightThreshold, float minDesertRockHeightThreshold)
{
	// set shader's terrain specific variables
	glUniform1i(shaderIsGeomTerrainLocation, true);
	glUniform1i(shaderIsFragTerrainLocation, true);

	glUniformMatrix4fv(shaderFrontLeftVertModelMatrixLocation, 1, GL_FALSE, glm::value_ptr(frontLeftVertModelMatrix));
	glUniformMatrix4fv(shaderFrontRightVertModelMatrixLocation, 1, GL_FALSE, glm::value_ptr(frontRightVertModelMatrix));
	glUniformMatrix4fv(shaderBackRightVertModelMatrixLocation, 1, GL_FALSE, glm::value_ptr(backRightVertModelMatrix));
	glUniformMatrix4fv(shaderBackLeftVertModelMatrixLocation, 1, GL_FALSE, glm::value_ptr(backLeftVertModelMatrix));

	glUniform1i(shaderBeachSandTextureLocation, SHADER_BEACH_SAND_TEXTURE_UNIT);
	glUniform1i(shaderPlainsGrassTextureLocation, SHADER_PLAINS_GRASS_TEXTURE_UNIT);
	glUniform1i(shaderPlainsRockTextureLocation, SHADER_PLAINS_ROCK_TEXTURE_UNIT);
	glUniform1i(shaderPlainsSnowTextureLocation, SHADER_PLAINS_SNOW_TEXTURE_UNIT);
	glUniform1i(shaderDesertSandTextureLocation, SHADER_DESERT_SAND_TEXTURE_UNIT);
	glUniform1i(shaderDesertRockTextureLocation, SHADER_DESERT_ROCK_TEXTURE_UNIT);

	glUniform1f(shaderMinPlainsHumidityThresholdLocation, minPlainsHumidityThreshold);

	glUniform1f(shaderMinPlainsGrassHeightThresholdLocation, minPlainsGrassHeightThreshold);
	glUniform1f(shaderMinPlainsRockHeightThresholdLocation, minPlainsRockHeightThreshold);
	glUniform1f(shaderMinPlainsSnowHeightThresholdLocation, minPlainsSnowHeightThreshold);
	glUniform1f(shaderMinDesertSandHeightThresholdLocation, minDesertSandHeightThreshold);
	glUniform1f(shaderMinDesertRockHeightThresholdLocation, minDesertRockHeightThreshold);
}


void TerrainShader::SetShaderWaterValues(glm::mat4 waterModelMatrix)
{
	// set shader's water specific variables
	glUniform1i(shaderIsGeomTerrainLocation, false);
	glUniform1i(shaderIsFragTerrainLocation, false);

	glUniform1i(shaderWaterTextureLocation, SHADER_WATER_TEXTURE_UNIT);
	
	glUniformMatrix4fv(shaderWaterModelMatrixLocation, 1, GL_FALSE, glm::value_ptr(waterModelMatrix));
}

TerrainShader::~TerrainShader()
{

}