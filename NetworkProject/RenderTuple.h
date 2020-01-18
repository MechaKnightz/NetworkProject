#pragma once
#include <boost\smart_ptr\shared_ptr.hpp>
class TransformComponent;
class ModelComponent;

struct RenderTuple {
	RenderTuple(std::shared_ptr<TransformComponent> transformComponent, std::shared_ptr<ModelComponent> modelComponent) : transformComponent(transformComponent), modelComponent(modelComponent)
	{

	}
	std::shared_ptr<TransformComponent> transformComponent;
	std::shared_ptr<ModelComponent> modelComponent;
};