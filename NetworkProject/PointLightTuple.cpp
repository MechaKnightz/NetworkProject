#include "PointLightTuple.h"
#include <vector>
#include <map>
#include "Entity.h"
#include "PointLightComponent.h"
#include "TransformComponent.h"

std::vector<std::shared_ptr<PointLightTuple>> PointLightTuple::GetPointLightTuples(std::map<uint32_t, std::shared_ptr<Entity>>& entities)
{
	auto list = std::vector<std::shared_ptr<PointLightTuple>>();

	for (const auto& entity : entities)
	{
		std::shared_ptr<TransformComponent> transformComponent;
		for (const auto& component : entity.second->Components)
		{
			if (auto shader = std::dynamic_pointer_cast<TransformComponent>(component)) {
				transformComponent = shader;
			}
		}
		if (transformComponent == nullptr) continue;
		std::shared_ptr<PointLightComponent> lightComponent;
		for (const auto& component : entity.second->Components)
		{
			if (auto light = std::dynamic_pointer_cast<PointLightComponent>(component)) {
				lightComponent = light;
			}
		}
		if (lightComponent == nullptr) continue;

		auto tuple = std::make_shared<PointLightTuple>();
		tuple->Transform = transformComponent;
		tuple->PointLight = lightComponent;
		list.push_back(tuple);
	}
	return list;
}