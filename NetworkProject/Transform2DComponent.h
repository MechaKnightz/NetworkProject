#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include "Component.h"

class Transform2DComponent : public Component
{
public:
	Transform2DComponent(glm::vec2 pos = glm::vec2(0), float rot = 0 , glm::vec3 scale = glm::vec3(1))
	{
		Position = pos;
		Rotation = rot;
		Scale = scale;
	}

	glm::vec2 Position;
	float Rotation;
	glm::vec2 Scale;
};