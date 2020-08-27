#pragma once
#include "Entity.h"
#include <map>
#include <memory>

class ModelComponent;
class TransformComponent;

struct RenderTuple {
	std::shared_ptr<TransformComponent> Transform;
	std::shared_ptr<ModelComponent> Model;

	static std::vector<std::shared_ptr<RenderTuple>> GetRenderTuples(std::map<uint32_t, std::shared_ptr<Entity>>& entities);

};