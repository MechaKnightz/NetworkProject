#include "InputSystem.h"
#include <iostream>
#include "EntityAdmin.h"
#include <GLFW\glfw3.h>
#include "TransformComponent.h"

void updateCameraVectors(std::shared_ptr<CameraComponent> camera)
{
	// Calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(camera->Yaw)) * cos(glm::radians(camera->Pitch));
	front.y = sin(glm::radians(camera->Pitch));
	front.z = sin(glm::radians(camera->Yaw)) * cos(glm::radians(camera->Pitch));
	camera->Front = glm::normalize(front);
	// Also re-calculate the Right and Up vector
	camera->Right = glm::normalize(glm::cross(camera->Front, camera->WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	camera->Up = glm::normalize(glm::cross(camera->Right, camera->Front));
}

InputSystem::InputSystem(EntityAdmin* admin) : System(admin)
{
	auto inputComponent = admin->GetSingle<InputComponent>();
	auto windowComponent = admin->GetSingle<WindowComponent>();
	
	inputComponent->KeysToCheck.push_back(GLFW_KEY_ESCAPE);
	inputComponent->KeysToCheck.push_back(GLFW_KEY_UP);
	inputComponent->KeysToCheck.push_back(GLFW_KEY_DOWN);
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
	auto cameraComponent = admin->GetSingle<CameraComponent>();

	for (const auto& key : inputComponent->KeysToCheck)
	{
		inputComponent->KeyStatus[key] = glfwGetKey(windowComponent->window, key);

		if(key == GLFW_KEY_ESCAPE && inputComponent->KeyStatus[key] == GLFW_PRESS)
			glfwSetWindowShouldClose(windowComponent->window, true);

		auto renderTuple = admin->GetRenderTuple();

		if (key == GLFW_KEY_UP && inputComponent->KeyStatus[key] == GLFW_PRESS)
		{
			renderTuple[0]->transformComponent->Position.y += timestep * 10;
			shaderComponent->MixValue += 0.001f; // change this value accordingly (might be too slow or too fast based on system hardware)
			if (shaderComponent->MixValue >= 1.0f)
				shaderComponent->MixValue = 1.0f;
		}
		if (key == GLFW_KEY_DOWN && inputComponent->KeyStatus[key] == GLFW_PRESS)
		{
			renderTuple[0]->transformComponent->Position.y -= timestep * 10;
			shaderComponent->MixValue -= 0.001f; // change this value accordingly (might be too slow or too fast based on system hardware)
			if (shaderComponent->MixValue <= 0.0f)
				shaderComponent->MixValue = 0.0f;
		}
		if (key == GLFW_KEY_W && inputComponent->KeyStatus[key] == GLFW_PRESS)
		{
			cameraComponent->Position += cameraComponent->Front * cameraComponent->MovementSpeed * timestep;
		}
		if (key == GLFW_KEY_A && inputComponent->KeyStatus[key] == GLFW_PRESS)
		{
			cameraComponent->Position -= cameraComponent->Right * cameraComponent->MovementSpeed * timestep;
		}
		if (key == GLFW_KEY_S && inputComponent->KeyStatus[key] == GLFW_PRESS)
		{
			cameraComponent->Position -= cameraComponent->Front * cameraComponent->MovementSpeed * timestep;
		}
		if (key == GLFW_KEY_D && inputComponent->KeyStatus[key] == GLFW_PRESS)
		{
			cameraComponent->Position += cameraComponent->Right * cameraComponent->MovementSpeed * timestep;
		}
		if (key == GLFW_KEY_SPACE && inputComponent->KeyStatus[key] == GLFW_PRESS)
		{
			cameraComponent->Position += cameraComponent->Up * cameraComponent->MovementSpeed * timestep;
		}
		if (key == GLFW_KEY_LEFT_CONTROL && inputComponent->KeyStatus[key] == GLFW_PRESS)
		{
			cameraComponent->Position -= cameraComponent->Up * cameraComponent->MovementSpeed * timestep;
		}
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

	xoffset *= cameraComponent->MouseSensitivity;
	yoffset *= cameraComponent->MouseSensitivity;

	cameraComponent->Yaw += xoffset;
	cameraComponent->Pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (cameraComponent->Pitch > 89.0f)
		cameraComponent->Pitch = 89.0f;
	if (cameraComponent->Pitch < -89.0f)
		cameraComponent->Pitch = -89.0f;

	// Update Front, Right and Up Vectors using the updated Euler angles
	updateCameraVectors(cameraComponent);

	inputComponent->OldMouseXPos = xpos;
	inputComponent->OldMouseYPos = ypos;
}
