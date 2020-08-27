#pragma once
#include <memory>
#include "Entity.h"
#include <map>
class TransformComponent;
class PointLightComponent;

struct PointLightTuple {
	std::shared_ptr<TransformComponent> Transform;
	std::shared_ptr<PointLightComponent> PointLight;

	static std::vector<std::shared_ptr<PointLightTuple>> GetPointLightTuples(std::map<uint32_t, std::shared_ptr<Entity>>& entities);
};