#include "EntityAdmin.h"
#include "InputSystem.h"
#include "WindowSystem.h"
#include "RenderSystem.h"
#include "ShaderComponent.h"
#include "TransformComponent.h"
#include "ModelComponent.h"
#include "Constants.h"
#include "FPSCounterComponent.h"
#include "FPSCounterSystem.h"

using namespace std;

glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};

EntityAdmin::EntityAdmin(GLFWwindow* window) : rd(), eng(rd()), distr(numeric_limits<uint32_t>::min(), numeric_limits<uint32_t>::max()), window(window)
{
	initSingleComponents();
	initSystems();
	InitEntities();

	//auto test = GetEntities<TransformComponent>();
	//auto test2 = GetEntities<ModelComponent>();
	//auto test = GetEntities<TransformComponent, ModelComponent>();
}

shared_ptr<Entity> EntityAdmin::CreateEntity()
{
	uint32_t temp = getUniqueID();
	shared_ptr<Entity> tempEnt = make_shared<Entity>(temp);
	entities.insert(pair<uint32_t, shared_ptr<Entity>>(temp, tempEnt));
	return tempEnt;
}

void EntityAdmin::initSystems()
{
	//systems.push_back(dynamic_pointer_cast<System>(std::make_shared<WindowSystem>(this)));
	systems.push_back(dynamic_pointer_cast<System>(std::make_shared<InputSystem>(this)));
	systems.push_back(dynamic_pointer_cast<System>(std::make_shared<RenderSystem>(this)));
	if(FPS_COUNTER) systems.push_back(dynamic_pointer_cast<System>(std::make_shared<FPSCounterSystem>(this)));
}

void EntityAdmin::initSingleComponents()
{
	singleComponents.push_back(dynamic_pointer_cast<Component>(std::make_shared<InputComponent>()));
	singleComponents.push_back(dynamic_pointer_cast<Component>(std::make_shared<WindowComponent>(this->window)));
	singleComponents.push_back(dynamic_pointer_cast<Component>(std::make_shared<ShaderComponent>("shaders/shader.vert", "shaders/shader.frag")));
	singleComponents.push_back(dynamic_pointer_cast<Component>(std::make_shared<CameraComponent>()));
	if(FPS_COUNTER) singleComponents.push_back(dynamic_pointer_cast<Component>(std::make_shared<FPSCounterComponent>()));
}

void EntityAdmin::InitEntities()
{
	for (const auto& cubePos : cubePositions)
	{
		auto ent = CreateEntity();
		ent->Components.push_back(make_shared<TransformComponent>(cubePos));
		ent->Components.push_back(make_shared<ModelComponent>());
	}
}

void EntityAdmin::Update(float timestep)
{
	//cout << getRandomUInt32() << endl;
	for(const auto& system : systems)
	{
		system->Update(timestep);
	}
}

void EntityAdmin::Draw(float interp)
{
	for (const auto& system : systems)
	{
		system->Draw(interp);
	}
}

std::vector<std::shared_ptr<RenderTuple>> EntityAdmin::GetRenderTuple()
{
	auto list = std::vector<std::shared_ptr<RenderTuple>>();
	
	for (const auto& tuple : entities)
	{
		shared_ptr<TransformComponent> transformComponent;
		for (const auto& entity : tuple.second->Components)
		{
			if (auto shader = dynamic_pointer_cast<TransformComponent>(entity)) {
				transformComponent = shader;
			}
		}
		if (transformComponent == nullptr) continue;
		shared_ptr<ModelComponent> cameraComponent;
		for (const auto& entity : tuple.second->Components)
		{
			if (auto camera = dynamic_pointer_cast<ModelComponent>(entity)) {
				cameraComponent = camera;
			}
		}
		if (cameraComponent == nullptr) continue;
		list.push_back(make_shared<RenderTuple>(transformComponent, cameraComponent));
	}
	return list;
}

uint32_t EntityAdmin::getUniqueID()
{
	for (uint32_t i = 0; i < numeric_limits<uint32_t>::max(); i++)
	{
		if (entities.find(i) == entities.end()) return i;
	}
	//ghetto way
	//while (true)
	//{
	//	uint32_t temp = getRandomUInt32();
	//	if (entities.find(temp) == entities.end()) return temp;
	//}
}
uint32_t EntityAdmin::getRandomUInt32()
{
    return distr(eng);
}
