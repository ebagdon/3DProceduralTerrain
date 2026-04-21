#pragma once

#include "Window.h"

#include <GLFW/include/glfw3.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Camera.h"
#include "Skybox.h"
#include "DirectionalLight.h"
#include "ChunkController.h"

class GraphicsManager
{
public:
	GraphicsManager();

	void Run();
	bool ProgramRunning();

	void WindowResizeProjectionMatrix();

	~GraphicsManager();

private:
	Window* applicationWindow;
	
	Camera* camera;
	float fov, nearPlane, farPlane;

	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	Skybox* skybox;

	DirectionalLight* directionalLight;

	double deltaTime;
	double lastTime;

	ChunkController* chunkController;

	void RenderScene();
};