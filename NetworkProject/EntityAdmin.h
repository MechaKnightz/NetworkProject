#pragma once
#include <string>
#include <map>
#include "Entity.h"
#include <vector>
#include <random>
#include <memory>
#include "RenderTuple.h"
#include "System.h"
#include <utility>
#include <iostream>
#include "PointLightTuple.h"
#include "ResourceManager.h"
#include "Component.h"
#include "Shader.h"
#include "CameraTuple.h"

class GLFWwindow;

class EntityAdmin : public std::enable_shared_from_this<EntityAdmin>
{
public:
	std::shared_ptr<Entity> CreateEntity();
	void Update(float timestep);
	void Draw(float interp);
	
	std::vector<std::shared_ptr<RenderTuple>> GetRenderTuples();

	std::vector<std::shared_ptr<PointLightTuple>> GetPointLightTuples();

	std::shared_ptr<CameraTuple> GetMainCamera();

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

	std::vector<std::shared_ptr<Shader>> GetShaders();

	//bool GetTypeInfo(std::shared_ptr<Entity> ent, const std::type_info& info)
	//{
	//	for (int i = 0; i < ent->Components.size(); i++)
	//	{
	//		auto test1 = typeid(*ent->Components[i]).name();
	//		auto test2 = info.name();

	//		if (info == typeid(*ent->Components[i])) {
	//			return true;
	//		}
	//	}
	//	return false;
	//}

	//template <class First, class ...T>
	//std::shared_ptr<std::vector<std::shared_ptr<Entity>>> GetEntitiesWithTypes(First first, T...)
	//{
	//	
	//}

	//template <class ...T>
	//std::shared_ptr<std::vector<std::shared_ptr<Entity>>> GetEntitiesWithTypes()
	//{
	//	auto ents = std::make_shared<std::vector<std::shared_ptr<Entity>>>();
	//	for (const auto& entity : entities)
	//	{
	//		std::vector<bool> dummy = { GetTypeInfo(entity.second, typeid(T))... };

	//		bool allTrue = true;
	//		for (int i = 0; i < dummy.size(); i++) {
	//			if (!dummy[i])
	//			{
	//				allTrue = false; //not all values in array are true
	//				break;
	//			}
	//		}
	//		if (allTrue) ents->push_back(entity.second);

	//	}
	//	return ents;
	//}

	//recursive entity creation functions
	template <class ...T>
	std::shared_ptr<Entity> CreateEntityTemplate(std::shared_ptr<Component> firstComp, std::shared_ptr<T>... components)
	{
		std::shared_ptr<Entity> ent = CreateEntity();
		CreateEntityTemplateRecursive(ent, firstComp, components...);
		return ent;
	}

	template <class ...T>
	void CreateEntityTemplateRecursive(std::shared_ptr<Entity> ent, std::shared_ptr<Component> firstComp, std::shared_ptr<T>... components)
	{
		ent->Components.push_back(firstComp);
		CreateEntityTemplateRecursive(ent, components...);
	}

	void CreateEntityTemplateRecursive(std::shared_ptr<Entity> ent)
	{

	}
	//end of recursive
	template <class ...T>
	void CreateEntityTemplate()
	{
		CreateEntity();
	}

	EntityAdmin(GLFWwindow* window);

	GLFWwindow* window;
private:
	std::map<uint32_t, std::shared_ptr<Entity>> entities;
	std::vector<std::shared_ptr<System>> systems;
	std::vector<std::shared_ptr<Component>> singleComponents;

	ResourceManager resMan;

	void CreateLightEntity(float x, float y, float z);

	void CreateModelEntity(float x, float y, float z, std::string path);

	uint32_t getUniqueID();
	uint32_t getRandomUInt32();

	void initSystems();
	void initSingleComponents();
	void InitEntities();

	std::random_device rd;
	std::mt19937 eng;
	std::uniform_int_distribution<uint32_t> distr;
};
