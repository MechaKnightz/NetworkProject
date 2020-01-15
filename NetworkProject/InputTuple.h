#pragma once
#include <memory>
class InputComponent;
class WindowComponent;
class ShaderComponent;
class CameraComponent;

struct InputTuple
{
	InputTuple(std::shared_ptr<InputComponent> inputComponent, std::shared_ptr<WindowComponent> windowComponent, std::shared_ptr<ShaderComponent> shaderComponent, std::shared_ptr<CameraComponent> cameraComponent) : inputComponent(inputComponent), windowComponent(windowComponent), shaderComponent(shaderComponent), cameraComponent(cameraComponent)
	{

	}
	std::shared_ptr<InputComponent> inputComponent;
	std::shared_ptr<WindowComponent> windowComponent;
	std::shared_ptr<ShaderComponent> shaderComponent;
	std::shared_ptr<CameraComponent> cameraComponent;
};