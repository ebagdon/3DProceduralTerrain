#include "Window.h"

Window::Window()
{
	// initialize window width and height
	width = 1200;
	height = 1200;
}

Window::Window(GLint windowWidth, GLint windowHeight)
{
	// initialize window width and height
	width = windowWidth;
	height = windowHeight;

	// initialize window
	Init();
}

bool Window::GetWindowShouldClose()
{
	// returns true if the user exits out of the window
	return glfwWindowShouldClose(applicationWindow);
}

void Window::Clear()
{
	// set clear color and then clear screen
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::Update()
{
	// handle window resizing and closing events
	glfwPollEvents();

	// swap buffers so we can see what has rendered
	glfwSwapBuffers(applicationWindow);
}

float Window::GetAspectRatio()
{
	// calculate and return the window's aspect ratio
	int width, height;
	glfwGetFramebufferSize(applicationWindow, &width, &height);

	return (float)width / (float)height;
}

double Window::GetXChange()
{
	// get x change, return it, and reset x change so that the camera doesn't keep moving
	double theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

double Window::GetYChange()
{
	// get y change, return it, and reset y change so that the camera doesn't keep moving
	double theChange = yChange;
	yChange = 0.0f;
	return theChange;
}

void Window::Init()
{
	// initialize GLFW
	if (!glfwInit())
	{
		printf("GLFW Initialisation failed!");
		glfwTerminate();
		return;
	}

	// Setup OpenGL context properties
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// create the window and check to make sure it was successfully created
	applicationWindow = glfwCreateWindow(width, height, "3D Procedural Terrain", NULL, NULL);
	if (!applicationWindow)
	{
		printf("GLFW window creation failed");
		glfwTerminate();
		return;
	}

	// Set context for GLEW to use
	glfwMakeContextCurrent(applicationWindow);

	// initialize glew and check if it did not initialize properly
	if (glewInit() != GLEW_OK)
	{
		printf("GLEW initialization failed!");
		glfwDestroyWindow(applicationWindow);
		glfwTerminate();
		return;
	}

	// get framebuffer size
	int framebufferWidth, framebufferHeight;
	glfwGetFramebufferSize(applicationWindow, &framebufferWidth, &framebufferHeight);

	// enable depth and stencil testing
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);

	// create viewport
	glViewport(0, 0, framebufferWidth, framebufferHeight);

	// set window user pointer and then set callbacks
	glfwSetWindowUserPointer(applicationWindow, this);
	glfwSetWindowSizeCallback(applicationWindow, WindowSizeCallback);
	glfwSetKeyCallback(applicationWindow, HandleKeys);
	glfwSetCursorPosCallback(applicationWindow, HandleMouse);

	// disable mouse
	glfwSetInputMode(applicationWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::WindowSizeCallback(GLFWwindow* window, int width, int height)
{
	// get a pointer to the window instance that called this callpoint
	Window* windowPointer = static_cast<Window*>(glfwGetWindowUserPointer(window));

	// resize viewport and set window resized to true so that the graphics manager knows the window has been resized
	glViewport(0, 0, width, height);
	windowPointer->windowResized = true;
}

void Window::HandleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
	// get the specific window class instance
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	// if escape key is pressed exit the program
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	// enable and disable the cursor when pressing the left shift key
	if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS)
	{
		if (!theWindow->cursorActive)
		{
			glfwSetInputMode(theWindow->applicationWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			theWindow->cursorActive = true;
		}
		else
		{
			double lastX, lastY;
			glfwGetCursorPos(theWindow->applicationWindow, &lastX, &lastY);
			theWindow->lastX = lastX;
			theWindow->lastY = lastY;
			
			glfwSetInputMode(theWindow->applicationWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			theWindow->cursorActive = false;
		}
	}

	// if a valid key is pressed set it's bool to true and if it's released set it to false
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
		}
	}
}

void Window::HandleMouse(GLFWwindow* window, double xPos, double yPos)
{
	// get the specific window class instance
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	// if this is the mouse's first movement initialize the lastX and lastY value so that the camera doesn't automatically rotate without moving mouse
	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	// calculate how much the mouse's position has changed
	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	// set the lastX and lastY to the current mouse position
	theWindow->lastX = xPos;
	theWindow->lastY = yPos;
}


Window::~Window()
{

}