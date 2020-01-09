#pragma once
#include "System.h"

class RenderSystem : public System
{
public:
	RenderSystem(EntityAdmin* admin);
	void Update(float timestep);
};

