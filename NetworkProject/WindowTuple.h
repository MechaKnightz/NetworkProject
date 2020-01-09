#pragma once
#include <memory>
class WindowComponent;

struct WindowTuple {
	WindowTuple(std::shared_ptr<WindowComponent> windowComponent) : windowComponent(windowComponent) {

	}
	std::shared_ptr<WindowComponent> windowComponent;
};