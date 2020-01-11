#include "WindowSystem.h"
#include "EntityAdmin.h"

WindowSystem::WindowSystem(EntityAdmin* admin) : System(admin)
{
	auto windowTuple = admin->GetWindowTuple();

	windowTuple->windowComponent->window = admin->window;
}