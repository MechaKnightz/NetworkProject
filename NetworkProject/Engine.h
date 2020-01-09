#pragma once
#include <cstdint>
#include <string>
#include "WindowHandler.h"
#include "EntityAdmin.h"
#include <memory>

namespace eng {
	class Engine
	{
	public:
		Engine(unsigned int windowWidth, unsigned int windowHeight, std::string windowName);
		int run();

	private:

		std::shared_ptr<WindowHandler> wh;
		std::shared_ptr<EntityAdmin> ea;

		int64_t getTickCount();
		int64_t getTime();

		void update();

		void render(float interp);

		int64_t startingTime;

		bool quit = false;

		const int TICKS_PER_SECOND = 100;
		const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
		const int MAX_FRAMESKIP = 20;
	};
}