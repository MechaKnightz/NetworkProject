#include "InputSystem.h"
#include <iostream>
#include "EntityAdmin.h"
#include <GLFW\glfw3.h>

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
	auto tuple = this->admin->GetInputTuple();
	
	tuple->inputComponent->KeysToCheck.push_back(GLFW_KEY_ESCAPE);
	tuple->inputComponent->KeysToCheck.push_back(GLFW_KEY_UP);
	tuple->inputComponent->KeysToCheck.push_back(GLFW_KEY_DOWN);
	tuple->inputComponent->KeysToCheck.push_back(GLFW_KEY_W);
	tuple->inputComponent->KeysToCheck.push_back(GLFW_KEY_A);
	tuple->inputComponent->KeysToCheck.push_back(GLFW_KEY_S);
	tuple->inputComponent->KeysToCheck.push_back(GLFW_KEY_D);
	tuple->inputComponent->KeysToCheck.push_back(GLFW_KEY_LEFT_CONTROL);
	tuple->inputComponent->KeysToCheck.push_back(GLFW_KEY_SPACE);

	glfwSetInputMode(tuple->windowComponent->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(tuple->windowComponent->window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
}

void InputSystem::Update(float timestep)
{
	auto tuple = this->admin->GetInputTuple();

	for (const auto& key : tuple->inputComponent->KeysToCheck)
	{
		tuple->inputComponent->KeyStatus[key] = glfwGetKey(tuple->windowComponent->window, key);

		if(key == GLFW_KEY_ESCAPE && tuple->inputComponent->KeyStatus[key] == GLFW_PRESS)
			glfwSetWindowShouldClose(tuple->windowComponent->window, true);

		if (key == GLFW_KEY_UP && tuple->inputComponent->KeyStatus[key] == GLFW_PRESS)
		{
			tuple->shaderComponent->mixValue += 0.001f; // change this value accordingly (might be too slow or too fast based on system hardware)
			if (tuple->shaderComponent->mixValue >= 1.0f)
				tuple->shaderComponent->mixValue = 1.0f;
		}
		if (key == GLFW_KEY_DOWN && tuple->inputComponent->KeyStatus[key] == GLFW_PRESS)
		{
			tuple->shaderComponent->mixValue -= 0.001f; // change this value accordingly (might be too slow or too fast based on system hardware)
			if (tuple->shaderComponent->mixValue <= 0.0f)
				tuple->shaderComponent->mixValue = 0.0f;
		}
		if (key == GLFW_KEY_W && tuple->inputComponent->KeyStatus[key] == GLFW_PRESS)
		{
			tuple->cameraComponent->Position += tuple->cameraComponent->Front * tuple->cameraComponent->MovementSpeed * timestep;
		}
		if (key == GLFW_KEY_A && tuple->inputComponent->KeyStatus[key] == GLFW_PRESS)
		{
			tuple->cameraComponent->Position -= tuple->cameraComponent->Right * tuple->cameraComponent->MovementSpeed * timestep;
		}
		if (key == GLFW_KEY_S && tuple->inputComponent->KeyStatus[key] == GLFW_PRESS)
		{
			tuple->cameraComponent->Position -= tuple->cameraComponent->Front * tuple->cameraComponent->MovementSpeed * timestep;
		}
		if (key == GLFW_KEY_D && tuple->inputComponent->KeyStatus[key] == GLFW_PRESS)
		{
			tuple->cameraComponent->Position += tuple->cameraComponent->Right * tuple->cameraComponent->MovementSpeed * timestep;
		}
		if (key == GLFW_KEY_SPACE && tuple->inputComponent->KeyStatus[key] == GLFW_PRESS)
		{
			tuple->cameraComponent->Position += tuple->cameraComponent->Up * tuple->cameraComponent->MovementSpeed * timestep;
		}
		if (key == GLFW_KEY_LEFT_CONTROL && tuple->inputComponent->KeyStatus[key] == GLFW_PRESS)
		{
			tuple->cameraComponent->Position -= tuple->cameraComponent->Up * tuple->cameraComponent->MovementSpeed * timestep;
		}
	}

	double xpos, ypos;
	glfwGetCursorPos(tuple->windowComponent->window, &xpos, &ypos);
	
	if (tuple->inputComponent->FirstMousePoll)
	{
		tuple->inputComponent->OldMouseXPos = xpos;
		tuple->inputComponent->OldMouseYPos = ypos;
		tuple->inputComponent->FirstMousePoll = false;
	}

	float xoffset = xpos - tuple->inputComponent->OldMouseXPos;
	float yoffset = tuple->inputComponent->OldMouseYPos - ypos;

	xoffset *= tuple->cameraComponent->MouseSensitivity;
	yoffset *= tuple->cameraComponent->MouseSensitivity;

	tuple->cameraComponent->Yaw += xoffset;
	tuple->cameraComponent->Pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (tuple->cameraComponent->Pitch > 89.0f)
		tuple->cameraComponent->Pitch = 89.0f;
	if (tuple->cameraComponent->Pitch < -89.0f)
		tuple->cameraComponent->Pitch = -89.0f;

	// Update Front, Right and Up Vectors using the updated Euler angles
	updateCameraVectors(tuple->cameraComponent);

	tuple->inputComponent->OldMouseXPos = xpos;
	tuple->inputComponent->OldMouseYPos = ypos;
}
