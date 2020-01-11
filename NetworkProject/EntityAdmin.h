#pragma once
#include <string>
#include <map>
#include "Entity.h"
#include <vector>
#include <random>
#include <memory>
#include "InputTuple.h"
#include "WindowTuple.h"
#include "ShaderTuple.h"
#include "System.h"
class GLFWwindow;

class EntityAdmin : public std::enable_shared_from_this<EntityAdmin>
{
public:
	void createEntity(std::string resource = NULL);
	void Update(float timestep);
	void Draw(float interp);
	template<class T> T getTuple();

	std::shared_ptr<InputTuple> GetInputTuple();
	std::shared_ptr<WindowTuple> GetWindowTuple();
	std::shared_ptr<ShaderTuple> GetShaderTuple();

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

	std::random_device rd;
	std::mt19937 eng;
	std::uniform_int_distribution<uint32_t> distr;
};