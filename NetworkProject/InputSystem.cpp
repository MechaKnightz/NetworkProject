#include "InputSystem.h"
#include <iostream>
#include "EntityAdmin.h"
#include <GLFW\glfw3.h>

InputSystem::InputSystem(EntityAdmin* admin) : System(admin)
{
	auto tuple = this->admin->GetInputTuple();
	
	tuple->inputComponent->keysToCheck.push_back(GLFW_KEY_ESCAPE);
}

void InputSystem::Update(float timestep)
{
	auto tuple = this->admin->GetInputTuple();

	for (const auto& key : tuple->inputComponent->keysToCheck)
	{
		tuple->inputComponent->keyStatus[key] = glfwGetKey(tuple->windowComponent->window, key);

		if(key == GLFW_KEY_ESCAPE && tuple->inputComponent->keyStatus[key] == GLFW_PRESS)
			glfwSetWindowShouldClose(tuple->windowComponent->window, true);
	}
}
