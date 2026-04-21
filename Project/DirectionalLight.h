#pragma once

#include "Light.h"

class DirectionalLight :
    public Light
{
public:
    DirectionalLight();
    DirectionalLight(bool use, GLfloat red, GLfloat green, GLfloat blue,
        GLfloat ambientIntensity, GLfloat diffuseIntensity,
        GLfloat xDir, GLfloat yDir, GLfloat zDir);

    glm::vec3 GetDirection() { return direction; }

    ~DirectionalLight();

private:
    glm::vec3 direction;
};