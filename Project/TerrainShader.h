#pragma once

#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GlobalTextureNumbers.h"

class TerrainShader : public Shader
{
public:
    TerrainShader();

    void SetShaderCommonValues(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 cameraPosition,
        bool directionalLightInUse, glm::vec3 directionalLightColor,
        float directionalLightAmbientIntensity, float directionalLightDiffuseIntensity, glm::vec3 directionalLightDirection,
        float specularIntensity, float shininess);

    void SetShaderTerrainValues(glm::mat4 frontLeftVertModelMatrix, glm::mat4 frontRightVertModelMatrix, glm::mat4 backRightVertModelMatrix, glm::mat4 backLeftVertModelMatrix,
        float minPlainsHumidityThreshold,
        float minPlainsGrassHeightThreshold, float minPlainsRockHeightThreshold, float minPlainsSnowHeightThreshold,
        float minDesertSandHeightThreshold, float minDesertRockHeightThreshold);
    void SetShaderWaterValues(glm::mat4 waterModelMatrix);

    ~TerrainShader();

private:
    const char* vertexShaderLocation;
    const char* geometryShaderLocation;
    const char* fragmentShaderLocation;

    GLuint shaderViewLocation, shaderProjectionLocation;
    GLuint shaderCameraPositionLocation;

    GLuint shaderDirectionalLightInUseLocation, shaderDirectionalLightColorLocation, 
        shaderDirectionalLightAmbientIntensityLocation, shaderDirectionalLightDiffuseIntensityLocation, shaderDirectionalLightDirectionLocation;
    GLuint shaderSpecularIntensityLocation, shaderShininessLocation;

    GLuint shaderIsGeomTerrainLocation, shaderIsFragTerrainLocation;

    GLuint shaderFrontLeftVertModelMatrixLocation, shaderFrontRightVertModelMatrixLocation,
        shaderBackRightVertModelMatrixLocation, shaderBackLeftVertModelMatrixLocation;

    GLuint shaderWaterModelMatrixLocation;

    GLuint shaderBeachSandTextureLocation, shaderPlainsGrassTextureLocation, shaderPlainsRockTextureLocation, shaderPlainsSnowTextureLocation,
        shaderDesertSandTextureLocation, shaderDesertRockTextureLocation,
        shaderWaterTextureLocation;
    
    GLuint shaderMinPlainsHumidityThresholdLocation;

    GLuint shaderMinPlainsGrassHeightThresholdLocation, shaderMinPlainsRockHeightThresholdLocation, shaderMinPlainsSnowHeightThresholdLocation,
        shaderMinDesertSandHeightThresholdLocation, shaderMinDesertRockHeightThresholdLocation;
};