#include "WindowSystem.h"
#include "EntityAdmin.h"

WindowSystem::WindowSystem(EntityAdmin* admin) : System(admin)
{
	auto windowComponent = admin->GetSingle<WindowComponent>();

	windowComponent->window = admin->window;
}