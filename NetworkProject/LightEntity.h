#pragma once
#include "Entity.h"
#include "TransformComponent.h"
#include "PointLightComponent.h"

class LightEntity : public Entity
{
public:
	LightEntity(int32_t id, glm::vec3 transform) : Entity(id)
	{
		Components.push_back(std::make_shared<TransformComponent>(transform));
		Components.push_back(std::make_shared<PointLightComponent>());
	}
};

