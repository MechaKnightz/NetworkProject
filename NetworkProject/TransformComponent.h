#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

class TransformComponent : public Component
{
public:
	TransformComponent(glm::vec3 pos = glm::vec3(0), glm::quat rot = glm::quat(0, 0, 0, 0), glm::vec3 scale = glm::vec3(1))
	{
		Position = pos;
		Rotation = rot;
		Scale = scale;
	}
	glm::vec3 Position;
	glm::quat Rotation;
	glm::vec3 Scale;
};