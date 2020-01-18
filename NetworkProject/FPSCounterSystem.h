#pragma once
#include "System.h"

class FPSCounterSystem : public System
{
public: 
	FPSCounterSystem(EntityAdmin* admin);
	void Draw(float interp);
};

