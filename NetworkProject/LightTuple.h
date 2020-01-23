#pragma once
#include <memory>
class TransformComponent;
class LightComponent;

struct LightTuple 
{
	LightTuple(std::shared_ptr<TransformComponent> transformComponent, std::shared_ptr<LightComponent> lightComponent) : transformComponent(transformComponent), lightComponent(lightComponent)
	{

	}
	std::shared_ptr<TransformComponent> transformComponent;
	std::shared_ptr<LightComponent> lightComponent;
};