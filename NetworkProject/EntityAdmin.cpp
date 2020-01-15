#include "EntityAdmin.h"
#include "InputSystem.h"
#include "WindowSystem.h"
#include "RenderSystem.h"
#include "ShaderComponent.h"

using namespace std;

shared_ptr<InputTuple> EntityAdmin::GetInputTuple()
{
	shared_ptr<WindowComponent> windowComponent;
	shared_ptr<InputComponent> inputComponent;
	shared_ptr<ShaderComponent> shaderComponent;
	shared_ptr<CameraComponent> cameraComponent;
	for (const auto& component : singleComponents)
	{
		if (auto input = dynamic_pointer_cast<InputComponent>(component)) {
			inputComponent = input;
		}
		if (auto window = dynamic_pointer_cast<WindowComponent>(component)) {
			windowComponent = window;
		}
		if (auto shader = dynamic_pointer_cast<ShaderComponent>(component)) {
			shaderComponent = shader;
		}
		if (auto camera = dynamic_pointer_cast<CameraComponent>(component)) {
			cameraComponent = camera;
		}
	}
	return make_shared<InputTuple>(inputComponent, windowComponent, shaderComponent, cameraComponent);
}

std::shared_ptr<WindowTuple> EntityAdmin::GetWindowTuple()
{
	shared_ptr<WindowComponent> windowComponent;
	for (const auto& component : singleComponents)
	{
		if (auto window = dynamic_pointer_cast<WindowComponent>(component)) {
			windowComponent = window;
		}
	}
	return make_shared<WindowTuple>(windowComponent);
}

std::shared_ptr<RenderTuple> EntityAdmin::GetShaderTuple()
{
	shared_ptr<ShaderComponent> shaderComponent;
	shared_ptr<CameraComponent> cameraComponent;
	for (const auto& component : singleComponents)
	{
		if (auto window = dynamic_pointer_cast<ShaderComponent>(component)) {
			shaderComponent = window;
		}
		if (auto camera = dynamic_pointer_cast<CameraComponent>(component)) {
			cameraComponent = camera;
		}
	}
	return make_shared<RenderTuple>(shaderComponent, cameraComponent);
}

EntityAdmin::EntityAdmin(GLFWwindow* window) : rd(), eng(rd()), distr(numeric_limits<uint32_t>::min(), numeric_limits<uint32_t>::max()), window(window)
{
	initSingleComponents();
	initSystems();
}

void EntityAdmin::createEntity(string resource)
{
	uint32_t temp = getUniqueID();
	entities.insert(pair<uint32_t, Entity*>(temp, new Entity(temp)));
}

void EntityAdmin::initSystems()
{
	//systems.push_back(dynamic_pointer_cast<System>(std::make_shared<WindowSystem>(this)));
	systems.push_back(dynamic_pointer_cast<System>(std::make_shared<InputSystem>(this)));
	systems.push_back(dynamic_pointer_cast<System>(std::make_shared<RenderSystem>(this)));
}

void EntityAdmin::initSingleComponents()
{
	singleComponents.push_back(dynamic_pointer_cast<Component>(std::make_shared<InputComponent>()));
	singleComponents.push_back(dynamic_pointer_cast<Component>(std::make_shared<WindowComponent>(this->window)));
	singleComponents.push_back(dynamic_pointer_cast<Component>(std::make_shared<ShaderComponent>("shaders/shader.vert", "shaders/shader.frag")));
	singleComponents.push_back(dynamic_pointer_cast<Component>(std::make_shared<CameraComponent>()));
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

template<class T>
inline T EntityAdmin::getTuple()
{

	return T();
}
