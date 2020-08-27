#pragma once
#include "System.h"
#include <memory>

class InputSystem : public System
{
public:
	InputSystem(EntityAdmin* admin);
	void Update(float timestep);
};

