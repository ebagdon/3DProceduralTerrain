#include "Light.h"

Light::Light()
{
	// initialize values
	inUse = false;
	color = glm::vec3(1.0f, 1.0f, 1.0f);
	aIntensity = 1.0f;
	dIntensity = 0.0f;
}

Light::Light(bool use, GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity, GLfloat diffuseIntensity)
{
	// initialize light settings
	inUse = use;
	color = glm::vec3(red, green, blue);
	aIntensity = ambientIntensity;
	dIntensity = diffuseIntensity;
}

Light::~Light()
{

}