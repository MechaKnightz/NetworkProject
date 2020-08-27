#include "Engine.h"
#include <glad/glad.h>
#include <chrono>
#include <iostream>
#include "Utility.h"
#include "GLFW/glfw3.h"

using namespace std;

Engine::Engine()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME.c_str(), NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}

	if (!VSYNC) glfwWindowHint(GLFW_DOUBLEBUFFER, GL_FALSE);

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
	ea = std::make_shared<EntityAdmin>(window);
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
	
	while (!glfwWindowShouldClose(window))
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
			glfwSwapBuffers(window);
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