#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

class TransformComponent {
	glm::vec3 Position;
	glm::quat Rotation;
	glm::vec3 Scale;
};