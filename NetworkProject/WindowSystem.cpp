#include "WindowSystem.h"
#include "EntityAdmin.h"
#include <glad\glad.h>
#include "GLFW/glfw3.h"
#include "WindowComponent.h"
#include "LightShaderComponent.h"
#include "ShaderComponent.h"
#include "SkyboxShaderComponent.h"

EntityAdmin* WindowSystem::staticAdmin;

WindowSystem::WindowSystem(EntityAdmin* admin) : System(admin), window(admin->window)
{
	WindowSystem::staticAdmin = admin;
	auto windowComponent = admin->GetSingle<WindowComponent>();

	windowComponent->window = window;
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	glfwSetFramebufferSizeCallback(window, FrambufferSizeCallback);

	windowComponent->ProjectionMatrix = CalculateMatrix(width, height);

	SetProjectionMatrices(windowComponent->ProjectionMatrix);

}

void WindowSystem::FrambufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);

	auto windowComponent = WindowSystem::staticAdmin->GetSingle<WindowComponent>();
	windowComponent->ProjectionMatrix = CalculateMatrix(width, height);

	SetProjectionMatrices(windowComponent->ProjectionMatrix);
}

glm::highp_mat4 WindowSystem::CalculateMatrix(int width, int height)
{
	return glm::perspective(glm::radians(90.0f), (float)width / (float)height, 0.1f, 100.0f);
}


void WindowSystem::SetProjectionMatrices(const glm::highp_mat4& projectionMatrix)
{

	for (const auto& shader : staticAdmin->GetShaders())
	{
		glUseProgram(shader->ID);
		shader->SetProjectionMatrix(projectionMatrix);
	}
}


void WindowSystem::Update(float timestep)
{

}