#pragma once

#include <cmath>
#include <cstdlib>
#include <ctime>

#include <GLEW/include/glew.h>

#include "FastNoiseLite.h"

class Noise
{
public:
	Noise();
	Noise(float humidityNoiseFrequency, float heightNoiseFrequency);

	float GetHumidityNoise(float x, float z);
	float GetHeightNoise(float x, float z);

	float GetMaxHeightNoise();

	~Noise();

private:
	FastNoiseLite noiseCreator;
	void SetSeed();
	float Get01Noise(float x, float z);

	float humidityFrequency, heightFrequency;
	float finalHeightNoiseSizeAmplitude = 5.0f;
};