#include "CameraTuple.h"
#include "CameraComponent.h"
#include "TransformComponent.h"

std::vector<std::shared_ptr<CameraTuple>> CameraTuple::GetCameraTuples(std::map<uint32_t, std::shared_ptr<Entity>>& entities)
{
	return std::vector<std::shared_ptr<CameraTuple>>(); //todo
}

std::shared_ptr<CameraTuple> CameraTuple::FromEntity(std::shared_ptr<Entity> entity)
{
	std::shared_ptr<TransformComponent> transformComponent;
	for (const auto& component : entity->Components)
	{
		if (auto shader = std::dynamic_pointer_cast<TransformComponent>(component)) {
			transformComponent = shader;
		}
	}
	if (transformComponent == nullptr) return nullptr;
	std::shared_ptr<CameraComponent> cameraComponent;
	for (const auto& component : entity->Components)
	{
		if (auto camera = std::dynamic_pointer_cast<CameraComponent>(component)) {
			cameraComponent = camera;
		}
	}
	if (cameraComponent == nullptr) return nullptr;

	auto tuple = std::make_shared<CameraTuple>();
	tuple->Camera = cameraComponent;
	tuple->Transform = transformComponent;
	return tuple;
}
