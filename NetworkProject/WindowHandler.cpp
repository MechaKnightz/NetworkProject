#include "WindowHandler.h"
#include <GLFW/glfw3.h>

WindowHandler::WindowHandler(unsigned int windowWidth, unsigned int windowHeight, std::string windowName) : WINDOW_WIDTH(windowWidth), WINDOW_HEIGHT(windowHeight)
{
	this->window = glfwCreateWindow(windowWidth, windowHeight, windowName.c_str(), NULL, NULL);
	glfwMakeContextCurrent(window);
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