#include "InputSystem.h"
#include <iostream>
#include "EntityAdmin.h"
#include <GLFW\glfw3.h>
#include "TransformComponent.h"
#include "LightShaderComponent.h"
#include "InputComponent.h"
#include "WindowComponent.h"
#include "ShaderComponent.h"
#include "CameraComponent.h"
#include <glm/glm.hpp>
#include "PerspectiveCameraComponent.h"
#include "MainCameraComponent.h"
#include "glm/gtc/quaternion.hpp"

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

void updateCameraVectors(std::shared_ptr<CameraTuple> camera)
{
	// Calculate the new Front vector
	glm::vec3 test(0.f);
	auto position = camera->Transform->Position;
	glm::vec3 front(0.f);
	auto mat = glm::rotate(front, camera->Transform->Rotation, glm::vec3(0, 0, -1));
	front = glm::normalize();
	auto right = glm::normalize(glm::cross(front, glm::vec3()));
	auto up = glm::normalize(glm::cross(right, front));
	auto lookAt =  glm::lookAt(position, position + front, up);
	

	//glm::vec3 front;
	//front.x = cos(glm::radians(camera->Yaw)) * cos(glm::radians(camera->Transform->Rotation ));//pu
	//front.y = sin(glm::radians(camera->Pitch));
	//front.z = sin(glm::radians(camera->Yaw)) * cos(glm::radians(camera->Pitch));
	//camera->Front = glm::normalize(front);
	//// Also re-calculate the Right and Up vector
	//camera->Right = glm::normalize(glm::cross(camera->Front, camera->WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	//camera->Up = glm::normalize(glm::cross(camera->Right, camera->Front));
}

InputSystem::InputSystem(EntityAdmin* admin) : System(admin)
{
	auto inputComponent = admin->GetSingle<InputComponent>();
	auto windowComponent = admin->GetSingle<WindowComponent>();
	
	inputComponent->KeysToCheck.push_back(GLFW_KEY_ESCAPE);
	inputComponent->KeysToCheck.push_back(GLFW_KEY_W);
	inputComponent->KeysToCheck.push_back(GLFW_KEY_A);
	inputComponent->KeysToCheck.push_back(GLFW_KEY_S);
	inputComponent->KeysToCheck.push_back(GLFW_KEY_D);
	inputComponent->KeysToCheck.push_back(GLFW_KEY_LEFT_CONTROL);
	inputComponent->KeysToCheck.push_back(GLFW_KEY_SPACE);

	glfwSetInputMode(windowComponent->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(windowComponent->window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
}

void InputSystem::Update(float timestep)
{
	auto inputComponent = admin->GetSingle<InputComponent>();
	auto windowComponent = admin->GetSingle<WindowComponent>();
	auto shaderComponent = admin->GetSingle<ShaderComponent>();
	auto cameraComponent = admin->GetMainCamera();
	auto lightShaderComponent = admin->GetSingle<LightShaderComponent>();

	for (const auto& key : inputComponent->KeysToCheck)
	{
		inputComponent->KeyStatus[key] = glfwGetKey(windowComponent->window, key);

		if(key == GLFW_KEY_ESCAPE && inputComponent->KeyStatus[key] == GLFW_PRESS)
			glfwSetWindowShouldClose(windowComponent->window, true);

		auto renderTuple = admin->GetRenderTuples();

		//if (key == GLFW_KEY_UP && inputComponent->KeyStatus[key] == GLFW_PRESS)
		//{
		//	lightShaderComponent->LightPos.y = lightShaderComponent->LightPos.y + 1.0f * timestep;
		//}
		//if (key == GLFW_KEY_DOWN && inputComponent->KeyStatus[key] == GLFW_PRESS)
		//{
		//	lightShaderComponent->LightPos.y = lightShaderComponent->LightPos.y - 1.0f * timestep;
		//}
		//if (key == GLFW_KEY_RIGHT && inputComponent->KeyStatus[key] == GLFW_PRESS)
		//{
		//	lightShaderComponent->LightPos.x = lightShaderComponent->LightPos.x + 1.0f * timestep;
		//}
		//if (key == GLFW_KEY_LEFT && inputComponent->KeyStatus[key] == GLFW_PRESS)
		//{
		//	lightShaderComponent->LightPos.x = lightShaderComponent->LightPos.x - 1.0f * timestep;
		//}
		//if (key == GLFW_KEY_PERIOD && inputComponent->KeyStatus[key] == GLFW_PRESS)
		//{
		//	lightShaderComponent->LightPos.z = lightShaderComponent->LightPos.z + 1.0f * timestep;
		//}
		//if (key == GLFW_KEY_COMMA && inputComponent->KeyStatus[key] == GLFW_PRESS)
		//{
		//	lightShaderComponent->LightPos.z = lightShaderComponent->LightPos.z - 1.0f * timestep;
		//}
		//if (key == GLFW_KEY_W && inputComponent->KeyStatus[key] == GLFW_PRESS)
		//{
		//	cameraComponent->Transform->Position += cameraComponent->Front * SPEED * timestep;
		//}
		//if (key == GLFW_KEY_A && inputComponent->KeyStatus[key] == GLFW_PRESS)
		//{
		//	cameraComponent->Transform->Position -= cameraComponent->Right * SPEED * timestep;
		//}
		//if (key == GLFW_KEY_S && inputComponent->KeyStatus[key] == GLFW_PRESS)
		//{
		//	cameraComponent->Transform->Position -= cameraComponent->Front * SPEED * timestep;
		//}
		//if (key == GLFW_KEY_D && inputComponent->KeyStatus[key] == GLFW_PRESS)
		//{
		//	cameraComponent->Transform->Position += cameraComponent->Right * SPEED * timestep;
		//}
		//if (key == GLFW_KEY_SPACE && inputComponent->KeyStatus[key] == GLFW_PRESS)
		//{
		//	cameraComponent->Transform->Position += cameraComponent->Up * SPEED * timestep;
		//}
		//if (key == GLFW_KEY_LEFT_CONTROL && inputComponent->KeyStatus[key] == GLFW_PRESS)
		//{
		//	cameraComponent->Transform->Position -= cameraComponent->Up * SPEED * timestep;
		//}
	}

	double xpos, ypos;
	glfwGetCursorPos(windowComponent->window, &xpos, &ypos);
	
	if (inputComponent->FirstMousePoll)
	{
		inputComponent->OldMouseXPos = xpos;
		inputComponent->OldMouseYPos = ypos;
		inputComponent->FirstMousePoll = false;
	}

	float xoffset = xpos - inputComponent->OldMouseXPos;
	float yoffset = inputComponent->OldMouseYPos - ypos;

	xoffset *= SENSITIVITY;
	yoffset *= SENSITIVITY;

	cameraComponent->Transform->Rotation = glm::rotate(cameraComponent->Transform->Rotation, xoffset, glm::vec3(0.f, 1.f, 0.f));
	cameraComponent->Transform->Rotation = glm::rotate(cameraComponent->Transform->Rotation, yoffset, glm::vec3(1.f, 0.f, 1.f));
	
	//cameraComponent->Yaw += xoffset;
	//cameraComponent->Pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	//if (cameraComponent->Pitch > 89.0f)
	//	cameraComponent->Pitch = 89.0f;
	//if (cameraComponent->Pitch < -89.0f)
	//	cameraComponent->Pitch = -89.0f;

	// Update Front, Right and Up Vectors using the updated Euler angles
	updateCameraVectors(cameraComponent);

	inputComponent->OldMouseXPos = xpos;
	inputComponent->OldMouseYPos = ypos;
}
