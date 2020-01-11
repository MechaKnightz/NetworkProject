#pragma once
#include <boost\smart_ptr\shared_ptr.hpp>
class ShaderComponent;

struct ShaderTuple {
	ShaderTuple(std::shared_ptr<ShaderComponent> shaderComponent) : shaderComponent(shaderComponent)
	{

	}
	std::shared_ptr<ShaderComponent> shaderComponent;
};