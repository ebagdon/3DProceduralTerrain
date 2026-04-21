#pragma once

#include <GLEW/include/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Light
{
public:
	Light();
	Light(bool use, GLfloat red, GLfloat green, GLfloat blue,
		GLfloat ambientIntensity, GLfloat diffuseIntensity);

	void SetInUse(bool use) { inUse = use; }

	bool GetInUse() { return inUse; }
	glm::vec3 GetColor() { return color; }
	GLfloat GetAmbientIntensity() {  return aIntensity; }
	GLfloat GetDiffuseIntensity() { return dIntensity; }

	~Light();

protected:
	bool inUse;

	glm::vec3 color;
	GLfloat aIntensity;
	GLfloat dIntensity;
};