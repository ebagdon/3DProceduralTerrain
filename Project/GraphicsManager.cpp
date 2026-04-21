#include "GraphicsManager.h"

GraphicsManager::GraphicsManager()
{
	// initialize window
	applicationWindow = new Window(2000, 1000);

	// initialize camera
	camera = new Camera(glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, -25.0f, 5.5f, 0.9f);

	// set variables for projection matrix
	fov = 60.0f;
	nearPlane = 0.1f;
	farPlane = 100.0f;

	// initialize matrices
	viewMatrix = camera->CalculateViewMatrix();
	projectionMatrix = glm::perspective(glm::radians(fov), applicationWindow->GetAspectRatio(), nearPlane, farPlane);

	// create our skybox
	skybox = new Skybox();

	// initialize the directional light
	directionalLight = new DirectionalLight(true, 1.0f, 1.0f, 1.0f, 0.2f, 0.6f, -1.0f, -1.0f, 0.0f);

	// initialize time variables
	deltaTime = 0.0f;
	lastTime = 0.0f;

	// initialize the chunk controller
	chunkController = new ChunkController(35);
}

void GraphicsManager::Run()
{
	// calculate delta time in seconds
	double now = glfwGetTime();
	deltaTime = now - lastTime;
	lastTime = now;

	// if the window has been resized recalculate the projection matrix
	if (applicationWindow->GetWindowResized())
	{
		WindowResizeProjectionMatrix();
		applicationWindow->SetWindowResized(false);
	}

	// clear window so we can draw new things
	applicationWindow->Clear();

	// calculate view matrix and then render the scene
	viewMatrix = camera->CalculateViewMatrix();
	skybox->DrawSkybox(viewMatrix, projectionMatrix);
	RenderScene();

	// update the window so we can see what we have drawn
	applicationWindow->Update();
}

bool GraphicsManager::ProgramRunning()
{
	// returns true if the program is still running
	return !applicationWindow->GetWindowShouldClose();
}

void GraphicsManager::WindowResizeProjectionMatrix()
{
	// calculate projection matrix
	projectionMatrix = glm::perspective(glm::radians(fov), applicationWindow->GetAspectRatio(), nearPlane, farPlane);
}

void GraphicsManager::RenderScene()
{
	// only be able to move around and look around with camera if the cursor is disabled
	if (!applicationWindow->GetCursorActive())
	{
		camera->KeyControl(applicationWindow->GetKeys(), (float)deltaTime);
		camera->MouseControl(applicationWindow->GetXChange(), applicationWindow->GetYChange());
	}
	
	// draw the chunks
	chunkController->DrawChunks(&viewMatrix, &projectionMatrix, camera->GetPosition(), directionalLight);
}

GraphicsManager::~GraphicsManager()
{

}