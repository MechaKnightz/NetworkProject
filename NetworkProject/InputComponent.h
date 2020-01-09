#pragma once
#include "Component.h"
#include <vector>
#include <map>

class InputComponent : public Component
{
public:
	std::vector<int> keysToCheck;
	std::map<int, int> keyStatus;
};

