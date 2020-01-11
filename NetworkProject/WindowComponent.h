#pragma once
#include "Component.h"

class GLFWwindow;
class WindowComponent : public Component
{
public:
	WindowComponent(GLFWwindow* window) : window(window) {

	}
	GLFWwindow* window;
};