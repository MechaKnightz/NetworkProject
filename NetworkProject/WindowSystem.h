#pragma once
#include "System.h"
#include "EntityAdmin.h"
#include <memory>
#include "WindowComponent.h"

class WindowSystem : public System
{
public:
	WindowSystem(EntityAdmin* admin);
};

