#pragma once
#include "System.h"
#include <memory>
#include "WindowComponent.h"

class GLFWwindow;
class WindowSystem : public System
{
	static void FrambufferSizeCallback(GLFWwindow* window, int width, int height);
	static glm::highp_mat4 CalculateMatrix(int width, int height);

	GLFWwindow* window;

	static EntityAdmin* staticAdmin;
	static void SetProjectionMatrices(const glm::highp_mat4& projectionMatrix);
public:
	WindowSystem(EntityAdmin* admin);

	void Update(float timestep);
};

