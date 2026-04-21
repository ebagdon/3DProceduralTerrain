#pragma once

#include <stdio.h>

#include <GLEW/include/glew.h>
#include <GLFW/include/glfw3.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);

	bool GetWindowShouldClose();
	void Clear();
	void Update();

	float GetAspectRatio();

	bool GetCursorActive() { return cursorActive; }

	bool GetWindowResized() { return windowResized; }
	void SetWindowResized(bool value) { windowResized = value; }

	bool* GetKeys() { return keys; }
	double GetXChange();
	double GetYChange();

	~Window();

private:
	void Init();

	static void WindowSizeCallback(GLFWwindow* window, int width, int height);

	GLFWwindow* applicationWindow;
	GLint width, height;

	bool windowResized = false;

	bool keys[1024];

	double lastX;
	double lastY;
	double xChange;
	double yChange;
	bool mouseFirstMoved = true;
	bool cursorActive = false;

	static void HandleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void HandleMouse(GLFWwindow* window, double xPos, double yPos);
};