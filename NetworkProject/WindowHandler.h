#pragma once
#include <string>

class GLFWwindow;
class WindowHandler
{
public:
	WindowHandler(unsigned int windowWidth, unsigned int windowHeight, std::string windowName);

	static void frambufferSizeCallback(GLFWwindow* window, int width, int height);

	const int WINDOW_WIDTH;
	const int WINDOW_HEIGHT;

	GLFWwindow* getWindow()
	{
		return window;
	}

	bool isWindowClosing();

private:
	GLFWwindow* window;
};

