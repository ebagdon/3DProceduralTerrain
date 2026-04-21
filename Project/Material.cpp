#include "Material.h"

Material::Material()
{
	// initialize 
	sIntensity = 1.0f;
	shine = 1.0f;
}

Material::Material(float specularIntensity, float shininess)
{
	// initialize 
	sIntensity = specularIntensity;
	shine = shininess;
}

Material::~Material()
{

}