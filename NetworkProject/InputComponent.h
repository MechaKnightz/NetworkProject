#pragma once
#include "Component.h"
#include <vector>
#include <map>

class InputComponent : public Component
{
public:
	std::vector<int> KeysToCheck;
	std::map<int, int> KeyStatus;

	double OldMouseXPos, OldMouseYPos;
	bool FirstMousePoll = true;
};

