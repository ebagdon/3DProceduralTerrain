#include "DirectionalLight.h"

DirectionalLight::DirectionalLight() : Light()
{
	// intialize values
	direction = glm::vec3(0.0f, -1.0f, 0.0f);
}

DirectionalLight::DirectionalLight(bool use, GLfloat red, GLfloat green, GLfloat blue,
	GLfloat ambientIntensity, GLfloat diffuseIntensity,
	GLfloat xDir, GLfloat yDir, GLfloat zDir) : Light(use, red, green, blue, ambientIntensity, diffuseIntensity)
{
	// intialize values
	direction = glm::vec3(xDir, yDir, zDir);
}


DirectionalLight::~DirectionalLight()
{

}
