#pragma once
#include <string>
#include <map>
#include "Entity.h"
#include <vector>
#include <random>
#include <memory>
#include "LightTuple.h"
#include "RenderTuple.h"
#include "System.h"
#include <utility>
#include <iostream>
#include "PointLightTuple.h"

class GLFWwindow;

class EntityAdmin : public std::enable_shared_from_this<EntityAdmin>
{
public:
	std::shared_ptr<Entity> CreateEntity();
	void Update(float timestep);
	void Draw(float interp);

	std::vector<std::shared_ptr<RenderTuple>> GetRenderTuples();
	std::vector<std::shared_ptr<PointLightTuple>> GetPointLightTuples();

	template <class T>
	std::shared_ptr<T> GetSingle()
	{
		for (const auto& component : singleComponents)
		{
			if (auto res = std::dynamic_pointer_cast<T>(component)) {
				return res;
			}
		}
	}

	template<class T, class ...Tupler> //todo finish
	bool WrapperFunction(std::shared_ptr<Entity> entity) {
		for (const auto& component : entity->Components)
		{
			if (auto input = dynamic_pointer_cast<T>(component)) {
				return true;
			}
		}
		return false;
	}

	template <class ...T> //todo finish
	std::vector<std::tuple<std::shared_ptr<T>...>> GetEntities()
	{
		auto res = std::vector<std::tuple<std::shared_ptr<T>...>>();
		for (const auto& tuple : entities)
		{
			auto allMatch = { (WrapperFunction<T>(tuple.second)) ... };

		}
		return res;
	}

	EntityAdmin(GLFWwindow* window);

	GLFWwindow* window;
private:
	std::map<uint32_t, std::shared_ptr<Entity>> entities;
	std::vector<std::shared_ptr<System>> systems;
	std::vector<std::shared_ptr<Component>> singleComponents;

	uint32_t getUniqueID();
	uint32_t getRandomUInt32();

	void initSystems();
	void initSingleComponents();
	void InitEntities();

	std::random_device rd;
	std::mt19937 eng;
	std::uniform_int_distribution<uint32_t> distr;
};
