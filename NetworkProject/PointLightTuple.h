#pragma once
#include <memory>
class TransformComponent;
class PointLightComponent;

struct PointLightTuple {
public:
	PointLightTuple(std::shared_ptr<TransformComponent> transformComponent, std::shared_ptr<PointLightComponent> pointLightComponent) : transformComponent(transformComponent), pointLightComponent(pointLightComponent)
	{

	}
	std::shared_ptr<TransformComponent> transformComponent;
	std::shared_ptr<PointLightComponent> pointLightComponent;
};