#include "Engine.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <iostream>
#include "Utility.h"

using namespace std;

Engine::Engine()
{
}

void Engine::Initialize()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	if(!VSYNC) glfwWindowHint(GLFW_DOUBLEBUFFER, GL_FALSE);


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
	//init vars
	int64_t startingTime = Utility::GetTime();
	double nextGameTick = (double)getTickCount(startingTime);
	int loops;
	int renders;
	float interp;

	float lastFrame = glfwGetTime();
	


	while (!wh->isWindowClosing())
	{

		loops = 0;
		int64_t tempvar = getTickCount(startingTime);
		while (tempvar > nextGameTick&& loops < MAX_FRAMESKIP)
		{
			//ghetto deltatime
			float currentFrame = glfwGetTime();
			float deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			update(deltaTime);

			nextGameTick += SKIP_TICKS;
			loops++;
		}

		interp = float(getTickCount(startingTime) + SKIP_TICKS - nextGameTick)
			/ float(SKIP_TICKS);

		render(interp);

		if (FPS_COUNTER)
		{

		}

		glfwPollEvents();
		if (VSYNC)
			glfwSwapBuffers(wh->getWindow());
		else 
			glFlush();
	}
	glfwTerminate();
	return;
}

int64_t Engine::getTickCount(int64_t startingTime)
{
	return Utility::GetTime() - startingTime;
}

void Engine::update(float timestep)
{
	ea->Update(timestep);
}

void Engine::render(float interp)
{
	ea->Draw(interp); //todo
}