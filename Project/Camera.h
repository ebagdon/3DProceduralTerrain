#pragma once

#include <GLEW/include/glew.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <GLFW/include/glfw3.h>

class Camera
{
public:
	Camera();
	Camera(glm::vec3 startPosition, glm::vec3 startUp, double startYaw, double startPitch, float startMoveSpeed, float startTurnSpeed);

	void KeyControl(bool* keys, float deltaTime);
	void MouseControl(double xChange, double yChange);

	glm::mat4 CalculateViewMatrix();

	glm::vec3 GetPosition();

	~Camera();

private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	double lastYaw;
	double lastPitch;

	double yaw;
	double pitch;

	float moveSpeed;
	float turnSpeed;

	void Update();
};