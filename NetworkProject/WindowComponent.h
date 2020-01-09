#pragma once
#include "Component.h"

class GLFWwindow;
class WindowComponent : public Component
{
public:
	GLFWwindow* window;
};