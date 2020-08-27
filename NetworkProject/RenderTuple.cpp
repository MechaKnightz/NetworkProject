#include "RenderTuple.h"
#include <vector>
#include <map>
#include "Entity.h"
#include <memory>
#include "TransformComponent.h"
#include "ModelComponent.h"

std::vector<std::shared_ptr<RenderTuple>> RenderTuple::GetRenderTuples(std::map<uint32_t, std::shared_ptr<Entity>>& entities)
{
	auto list = std::vector<std::shared_ptr<RenderTuple>>();

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
		std::shared_ptr<ModelComponent> modelComponent;
		for (const auto& component : entity.second->Components)
		{
			if (auto model = std::dynamic_pointer_cast<ModelComponent>(component)) {
				modelComponent = model;
			}
		}
		if (modelComponent == nullptr) continue;
		auto tuple = std::make_shared<RenderTuple>();
		tuple->Transform = transformComponent;
		tuple->Model = modelComponent;
		list.push_back(tuple);
	}
	return list;
}
