#pragma once
#include <string>

class GLFWwindow;
class WindowHandler
{
public:
	WindowHandler(GLFWwindow* window);

	static void frambufferSizeCallback(GLFWwindow* window, int width, int height);

	GLFWwindow* getWindow()
	{
		return window;
	}

	bool isWindowClosing();

private:
	GLFWwindow* window;
};

