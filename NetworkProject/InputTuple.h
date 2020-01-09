#pragma once
#include <memory>
class InputComponent;
class WindowComponent;

struct InputTuple
{
	InputTuple(std::shared_ptr<InputComponent> inputComponent, std::shared_ptr<WindowComponent> windowComponent) : inputComponent(inputComponent), windowComponent(windowComponent)
	{

	}
	std::shared_ptr<InputComponent> inputComponent;
	std::shared_ptr<WindowComponent> windowComponent;
};