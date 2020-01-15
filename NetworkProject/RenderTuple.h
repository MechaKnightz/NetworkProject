#pragma once
#include <boost\smart_ptr\shared_ptr.hpp>
class ShaderComponent;
class CameraComponent;

struct RenderTuple {
	RenderTuple(std::shared_ptr<ShaderComponent> shaderComponent, std::shared_ptr<CameraComponent> cameraComponent) : shaderComponent(shaderComponent), cameraComponent(cameraComponent)
	{

	}
	std::shared_ptr<ShaderComponent> shaderComponent;
	std::shared_ptr<CameraComponent> cameraComponent;
};