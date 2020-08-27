#pragma once
#include <memory>
#include "Entity.h"
#include <map>
class TransformComponent;
class CameraComponent;

struct CameraTuple {
	std::shared_ptr<TransformComponent> Transform;
	std::shared_ptr<CameraComponent> Camera;

	static std::vector<std::shared_ptr<CameraTuple>> GetCameraTuples(std::map<uint32_t, std::shared_ptr<Entity>>& entities);

	static std::shared_ptr<CameraTuple> FromEntity(std::shared_ptr<Entity> entity);
};