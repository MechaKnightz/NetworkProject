#pragma once
#include "Component.h"
#include <glm\ext\matrix_float4x4_precision.hpp>
#include <glm\ext\matrix_clip_space.hpp>

class GLFWwindow;
class WindowComponent : public Component
{
public:
	WindowComponent(GLFWwindow* window) : window(window) {
	}
	GLFWwindow* window;

	glm::highp_mat4 ProjectionMatrix;
};