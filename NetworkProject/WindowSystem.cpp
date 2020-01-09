#include "WindowSystem.h"

WindowSystem::WindowSystem(EntityAdmin* admin) : System(admin)
{
	auto windowTuple = admin->GetWindowTuple();

	windowTuple->windowComponent->window = admin->window;
}