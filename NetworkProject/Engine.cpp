#include "Engine.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <iostream>

using namespace std;

Engine::Engine(int windowWidth, int windowHeight, std::string windowName) : WINDOW_WIDTH(windowWidth), WINDOW_HEIGHT(windowHeight), WINDOW_NAME(windowName)
{
}

void Engine::Initialize()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME.c_str(), NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
	wh = std::make_shared<WindowHandler>(window);
	ea = std::make_shared<EntityAdmin>(wh->getWindow());
}

void Engine::Run() 
{
	int64_t startingTime = getTime();
	double nextGameTick = (double)getTickCount(startingTime);
	int loops;
	int renders;
	float interp;

	while (!wh->isWindowClosing())
	{

		loops = 0;
		int64_t tempvar = getTickCount(startingTime);
		while (tempvar > nextGameTick&& loops < MAX_FRAMESKIP)
		{
			update();

			nextGameTick += SKIP_TICKS;
			loops++;
		}

		interp = float(getTickCount(startingTime) + SKIP_TICKS - nextGameTick)
			/ float(SKIP_TICKS);

		render(interp);

		glfwPollEvents();
		glfwSwapBuffers(wh->getWindow());
	}
	glfwTerminate();
	return;
}

int64_t Engine::getTickCount(int64_t startingTime)
{
	return getTime() - startingTime;
}

int64_t Engine::getTime()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void Engine::update()
{
	ea->Update(0.0f); //todo
}

void Engine::render(float interp)
{
	ea->Draw(interp); //todo
}