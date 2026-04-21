#pragma once

class Material
{
public:
	Material();
	Material(float specularIntensity, float shininess);

	float GetSpecularIntensity() { return sIntensity; }
	float GetShininess() { return shine; }

	~Material();

private:
	float sIntensity, shine;
};