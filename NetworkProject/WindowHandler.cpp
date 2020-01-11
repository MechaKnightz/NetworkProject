#include "WindowHandler.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "Engine.h"

WindowHandler::WindowHandler(GLFWwindow* window) : window(window)
{
	glfwSetFramebufferSizeCallback(window, frambufferSizeCallback);
}


void WindowHandler::frambufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

bool WindowHandler::isWindowClosing()
{
	return glfwWindowShouldClose(window);
}