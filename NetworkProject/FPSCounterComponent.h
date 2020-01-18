#pragma once
#include "Component.h"
#include <cstdint>
#include "Utility.h"

class FPSCounterComponent : public Component
{
public: 
	uint16_t Counter;
	uint64_t PreviousTime;

	FPSCounterComponent()
	{
		PreviousTime = Utility::GetTime();
		Counter = 0;
	}
};