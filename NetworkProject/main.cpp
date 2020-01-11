#include "Engine.h"
#include <iostream>
#include <memory>

int WINDOW_WIDTH = 1600;
int WINDOW_HEIGHT = 900;
std::string WINDOW_NAME = "NetworkProject";

int main()
{
	std::unique_ptr<Engine> engine = std::make_unique<Engine>(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME);
    engine->Initialize();
    engine->Run();
    return 0;
}