#pragma once
#include <memory>

class EntityAdmin;
class ResourceManager
{
	EntityAdmin* admin;
public:
	ResourceManager(EntityAdmin* admin);

	template <class T>
	std::shared_ptr<T> CreateComponent(const T& input)
	{
		return make_shared<T>(std::move(input));
	}
};

