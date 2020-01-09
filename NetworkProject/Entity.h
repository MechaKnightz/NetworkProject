#pragma once
#include <cstdint>
#include <vector>
class Component;
class Entity
{
public:
	Entity(int32_t id);
private:
	int32_t entityID;
	std::vector<Component*> components;
};

