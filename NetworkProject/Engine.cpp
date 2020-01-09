#include "Engine.h"
#include <chrono>
#include <GLFW/glfw3.h>
#include <iostream>

namespace eng {

	Engine::Engine(unsigned int windowWidth, unsigned int windowHeight, std::string windowName)
	{
		wh = std::make_shared<WindowHandler>(windowWidth, windowHeight, windowName);
		ea = std::make_shared<EntityAdmin>(wh->getWindow());
	}

	int Engine::run() {

		startingTime = getTime();
		double nextGameTick = (double)getTickCount();
		int loops;
		int renders;
		float interp;

		while (!wh->isWindowClosing())
		{

			loops = 0;
			int64_t tempvar = getTickCount();
			while (tempvar > nextGameTick && loops < MAX_FRAMESKIP)
			{
				update();

				nextGameTick += SKIP_TICKS;
				loops++;
			}

			interp = float(getTickCount() + SKIP_TICKS - nextGameTick)
				/ float(SKIP_TICKS);

			render(interp);

			glfwPollEvents();
			glfwSwapBuffers(wh->getWindow());
		}
		glfwTerminate();
		return 0;
	}

	int64_t Engine::getTickCount()
	{
		return getTime() - startingTime;
	}

	int64_t Engine::getTime()
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	}

	void Engine::update()
	{
		ea->update(0.0f); //todo
	}

	void Engine::render(float interp)
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
}