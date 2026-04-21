#include "Camera.h"

Camera::Camera()
{
	// initialize values
	position = glm::vec3(0.0f, 2.0f, 2.0f);
	worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	yaw = 0.0f;
	pitch = 0.0f;

	moveSpeed = 10.0f;
	turnSpeed = 10.0f;

	// update camera rotation
	Update();
}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, double startYaw, double startPitch, float startMoveSpeed, float startTurnSpeed)
{
	// initialize values
	position = startPosition;
	worldUp = startUp;
	yaw = startYaw;
	pitch = startPitch;

	moveSpeed = startMoveSpeed;
	turnSpeed = startTurnSpeed;

	// update camera rotation
	Update();
}

// handle camera movement
void Camera::KeyControl(bool* keys, float deltaTime)
{
	// calculate speed to move the camera based on the framerate of the program
	float velocity = moveSpeed * deltaTime;

	if (keys[GLFW_KEY_W])
	{
		position += front * velocity;
	}

	if (keys[GLFW_KEY_S])
	{
		position -= front * velocity;
	}

	if (keys[GLFW_KEY_A])
	{
		position -= right * velocity;
	}

	if (keys[GLFW_KEY_D])
	{
		position += right * velocity;
	}
}

void Camera::MouseControl(double xChange, double yChange)
{
	// calculate amount of rotation
	xChange *= turnSpeed;
	yChange *= turnSpeed;

	// add rotation to yaw and pitch
	yaw += xChange;
	pitch += yChange;

	// keep pitch from going too high
	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}

	// keep pitch from going too low
	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	// update camera rotation
	Update();
}

glm::mat4 Camera::CalculateViewMatrix()
{
	// create and return a view matrix
	return glm::lookAt(position, position + front, up);
}

glm::vec3 Camera::GetPosition()
{
	return position;
}

void Camera::Update()
{
	// calculate the point for the camera to look at
	front.x = (float)(cos(glm::radians(yaw)) * cos(glm::radians(pitch)));
	front.y = (float)(sin(glm::radians(pitch)));
	front.z = (float)(sin(glm::radians(yaw)) * cos(glm::radians(pitch)));
	front = glm::normalize(front);

	// calculate the camera's right and up vectors
	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}

Camera::~Camera()
{

}