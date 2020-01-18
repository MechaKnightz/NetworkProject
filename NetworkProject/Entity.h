#pragma once
#include <cstdint>
#include <vector>
#include <memory>
class Component;
class Entity
{
public:
	Entity(int32_t id);
	std::vector<std::shared_ptr<Component>> Components;
private:
	int32_t entityID;
};

