#include "Noise.h"

Noise::Noise()
{
	// initialize the noise creator
	noiseCreator.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	SetSeed();
	humidityFrequency = 1.0f;
	heightFrequency = 0.1f;
}

Noise::Noise(float humidityNoiseFrequency, float heightNoiseFrequency)
{
	// initialize the noise creator
	noiseCreator.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	SetSeed();
	humidityFrequency = humidityNoiseFrequency;
	heightFrequency = heightNoiseFrequency;
}

float Noise::GetHumidityNoise(float x, float z)
{
	// set the frequency of noise
	noiseCreator.SetFrequency(humidityFrequency);

	// create the first noise octave
	float firstOctaveAmplitude = 100.0f;
	float firstOctaveWavelength = 30.0f;
	float firstOctaveOffset = 100.0f;
	float firstOctave = firstOctaveAmplitude * Get01Noise((x + firstOctaveOffset) / firstOctaveWavelength, (z + firstOctaveOffset) / firstOctaveWavelength);

	// create the first noise octave
	float secondOctaveAmplitude = 70.0f;
	float secondOctaveWavelength = 40.0f;
	float secondOctaveOffset = 200.0f;
	float secondOctave = secondOctaveAmplitude * Get01Noise((x + secondOctaveOffset) / secondOctaveWavelength, (z + secondOctaveOffset) / secondOctaveWavelength);

	// convert the noise back to the 0 to 1 range
	float noise = (firstOctave + secondOctave) / (firstOctaveAmplitude + secondOctaveAmplitude);

	// smooth the terrain
	float redistribution = 0.9f;
	noise = pow(noise, redistribution);

	// return the final noise value
	return noise;
}

float Noise::GetHeightNoise(float x, float z)
{
	// set the frequency of noise
	noiseCreator.SetFrequency(heightFrequency);

	// create the first noise octave
	float firstOctaveAmplitude = 100.0f;
	float firstOctaveWavelength = 7.5f;
	float firstOctave = firstOctaveAmplitude * Get01Noise(x / firstOctaveWavelength, z / firstOctaveWavelength);
	
	// create the second noise octave
	float secondOctaveAmplitude = 75.0f;
	float secondOctaveWavelength = 5.0f;
	float secondOctaveOffset = 1.0f;
	float secondOctave = secondOctaveAmplitude * Get01Noise((x + secondOctaveOffset) / secondOctaveWavelength, (z + secondOctaveOffset) / secondOctaveWavelength);

	// create the third noise octave
	float thirdOctaveAmplitude = 50.0f;
	float thirdOctaveWavelength = 2.5f;
	float thirdOctaveOffset = 2.0f;
	float thirdOctave = thirdOctaveAmplitude * Get01Noise((x + thirdOctaveOffset) / thirdOctaveWavelength, (z + thirdOctaveOffset) / thirdOctaveWavelength);

	// create the fourth noise octave
	float fourthOctaveAmplitude = 20.0f;
	float fourthOctaveWavelength = 1.2f;
	float fourthOctaveOffset = 3.0f;
	float fourthOctave = fourthOctaveAmplitude * Get01Noise((x + fourthOctaveOffset) / fourthOctaveWavelength, (z + fourthOctaveOffset) / fourthOctaveWavelength);

	// convert the noise back to the 0 to 1 range
	float noise = (firstOctave + secondOctave + thirdOctave + fourthOctave) 
		/ (firstOctaveAmplitude + secondOctaveAmplitude + thirdOctaveAmplitude + fourthOctaveAmplitude);

	// smooth the terrain
	float redistribution = 3.85f;
	noise = pow(noise, redistribution);

	// make the max noise height larger and then return it
	return noise * finalHeightNoiseSizeAmplitude;
}

float Noise::GetMaxHeightNoise()
{
	// return the max possible noise value
	return finalHeightNoiseSizeAmplitude;
}

void Noise::SetSeed()
{
	// generate a random seed each time the program is run and use it to set the noiseCreator's seed
	srand((unsigned int)time(0));
	int seed = rand();
	noiseCreator.SetSeed(seed);
}

float Noise::Get01Noise(float x, float z)
{
	// create noise in a 0 to 1 range
	float noise = noiseCreator.GetNoise(x, z);
	return (noise - -1.0f) / 2.0f;
}

Noise::~Noise()
{

}