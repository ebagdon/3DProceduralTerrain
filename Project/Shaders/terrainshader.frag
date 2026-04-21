#version 330

// vertex's color, texture coordinate, and normal
in vec4 geomVertColor;
in vec2 geomTexCoord;
in vec3 geomNormal;

// position of the current fragment, the fragment's humidity noise value, and the fragment's height noise value
in vec3 geomFragPos;
in float geomHumidityNoise;
in float geomFragHeightNoise;

// fragment's output color
out vec4 finalColor;

// light data
struct Light
{
	vec3 color;
	float ambientIntensity;
	float diffuseIntensity;
};

// directional light data
struct DirectionalLight
{
	bool inUse;

	Light base;
	vec3 direction;
};

// material data
struct Material
{
	float specularIntensity;
	float shininess;
};

// position of the camera
uniform vec3 cameraPosition;

// directional light
uniform DirectionalLight directionalLight;

// bool to hold rather or not we are rendering terrain
uniform bool isFragTerrain;

// terrain textures
uniform sampler2D beachSandTexture;
uniform sampler2D plainsGrassTexture;
uniform sampler2D plainsRockTexture;
uniform sampler2D plainsSnowTexture;
uniform sampler2D desertSandTexture;
uniform sampler2D desertRockTexture;
uniform sampler2D waterTexture;

// material
uniform Material material;

// humidity threshold for plains biome if humidity does not meet this threshold the biome is set to desert
uniform float minPlainsHumidityThreshold;

// the height thresholds for different height textures
uniform float minPlainsGrassHeightThreshold;
uniform float minPlainsRockHeightThreshold;
uniform float minPlainsSnowHeightThreshold;
uniform float minDesertSandHeightThreshold;
uniform float minDesertRockHeightThreshold;

// determines how to light a fragment based on the directional light
vec4 CalcLightByDirection(Light light, vec3 direction);

// calculates the texture to use based on terrain humidity and height
vec4 CalculateTerrainTexture();

void main()
{
	// if we are rendering terrain
	if (isFragTerrain)
	{
		// set color of fragment
		finalColor = directionalLight.inUse ? CalculateTerrainTexture() * geomVertColor * CalcLightByDirection(directionalLight.base, -directionalLight.direction) : CalculateTerrainTexture() * geomVertColor;
	}
	else // if we are rendering water
	{
		// set color of fragment
		finalColor = directionalLight.inUse ? texture(waterTexture, geomTexCoord) * geomVertColor * CalcLightByDirection(directionalLight.base, -directionalLight.direction) :  texture(waterTexture, geomTexCoord) * geomVertColor;
	}
}

// determines how to light a fragment based on the directional light
vec4 CalcLightByDirection(Light light, vec3 direction)
{
	// calculate how much ambient light there should be
	vec4 ambientColor = vec4(light.color, 1.0) * light.ambientIntensity;

	// calculate how much diffuse light there should be
	float diffuseFactor = max(dot(normalize(geomNormal), normalize(direction)), 0.0f);
	vec4 diffuseColor = vec4(light.color, 1.0) * light.diffuseIntensity * diffuseFactor;
	
	// calculate how much specular light there should be
	vec4 specularColor = vec4(0, 0, 0, 0);
	if (diffuseFactor > 0.0)
	{
		vec3 fragToCamera = normalize(cameraPosition - geomFragPos);
		vec3 reflectedVertex = normalize(reflect(-direction, normalize(geomNormal)));
		float specularFactor = dot(fragToCamera, reflectedVertex);
		if (specularFactor > 0.0f)
		{
			specularFactor = pow(specularFactor, material.shininess);
			specularColor = vec4(light.color * material.specularIntensity * specularFactor, 1.0);
		}
	}

	// return the combined result of ambient light, diffuse light, and specular light
	return (ambientColor + diffuseColor + specularColor);
}

// calculates the texture to use based on terrain humidity and height
vec4 CalculateTerrainTexture()
{
	// color is set to the beach sand texture by default for if we do not meet any of the humidity and height criteria
	vec4 color = texture(beachSandTexture, geomTexCoord);
	
	// if we are in the plains biome
	if (geomHumidityNoise >= minPlainsHumidityThreshold)
	{
		// calculate which plains biome texture to use based on height
		if (geomFragHeightNoise >= minPlainsGrassHeightThreshold && geomFragHeightNoise < minPlainsRockHeightThreshold) { color = texture(plainsGrassTexture, geomTexCoord); return color; }
		else if (geomFragHeightNoise >= minPlainsRockHeightThreshold && geomFragHeightNoise < minPlainsSnowHeightThreshold) { color = texture(plainsRockTexture, geomTexCoord); return color;}
		else if (geomFragHeightNoise >= minPlainsSnowHeightThreshold) { color = texture(plainsSnowTexture, geomTexCoord); return color;}
	}
	else // if we are in the desert biome
	{
		// calculate which desert biome texture to use based on height
		if (geomFragHeightNoise >= minDesertSandHeightThreshold && geomFragHeightNoise < minDesertRockHeightThreshold) { color = texture(desertSandTexture, geomTexCoord); }
		else if (geomFragHeightNoise >= minDesertRockHeightThreshold) { color = texture(desertRockTexture, geomTexCoord); }
	}
	
	// return the texture
	return color;
}