#pragma once
#include <cstdint>
#include <string>
#include <memory>
#include "EntityAdmin.h"
#include "WindowHandler.h"

class Engine
{
public:
	Engine(int windowWidth, int windowHeight, std::string windowName);
	void Run();
	void Initialize();

private:

	const int WINDOW_WIDTH;
	const int WINDOW_HEIGHT;
	const std::string WINDOW_NAME;

	std::shared_ptr<WindowHandler> wh;
	std::shared_ptr<EntityAdmin> ea;

	int64_t getTickCount(int64_t startingTime);
	int64_t getTime();

	void update(float timestep);

	void render(float interp);

	bool quit = false;

	const int TICKS_PER_SECOND = 100;
	const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
	const int MAX_FRAMESKIP = 20;
};