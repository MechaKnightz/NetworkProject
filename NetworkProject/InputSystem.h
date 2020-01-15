#pragma once
#include "System.h"
#include "InputComponent.h"
#include <memory>
#include "WindowComponent.h"
#include "ShaderComponent.h"
#include "CameraComponent.h"

class InputSystem : public System
{
public:
	InputSystem(EntityAdmin* admin);
	void Update(float timestep);
};

