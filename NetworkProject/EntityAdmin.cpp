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
#include "LightComponent.h"
#include "LightShaderComponent.h"
#include "PointLightComponent.h"
#include "PointLightTuple.h"
#include "SkyboxComponent.h"
#include "SkyboxShaderComponent.h"
#include "MainCameraComponent.h"
#include "PerspectiveCameraComponent.h"
#include "CameraTuple.h"
#include "InputComponent.h"

using namespace std;

glm::vec3 cubePositions[] = {
  glm::vec3(-3.0f,  0.0f,  0.0f)/*,
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)*/
};

EntityAdmin::EntityAdmin(GLFWwindow* window) : rd(), eng(rd()), distr(numeric_limits<uint32_t>::min(), numeric_limits<uint32_t>::max()), window(window), resMan(this)
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
	systems.push_back(dynamic_pointer_cast<System>(std::make_shared<WindowSystem>(this)));
	systems.push_back(dynamic_pointer_cast<System>(std::make_shared<InputSystem>(this)));
	systems.push_back(dynamic_pointer_cast<System>(std::make_shared<RenderSystem>(this)));
	if(FPS_COUNTER) systems.push_back(dynamic_pointer_cast<System>(std::make_shared<FPSCounterSystem>(this)));
}

void EntityAdmin::initSingleComponents()
{
	singleComponents.push_back(dynamic_pointer_cast<Component>(std::make_shared<InputComponent>()));
	singleComponents.push_back(dynamic_pointer_cast<Component>(std::make_shared<WindowComponent>(this->window)));
	singleComponents.push_back(dynamic_pointer_cast<Component>(std::make_shared<ShaderComponent>("shaders/shader.vert", "shaders/shader.frag")));
	singleComponents.push_back(dynamic_pointer_cast<Component>(std::make_shared<LightShaderComponent>("shaders/lightShader.vert", "shaders/lightShader.frag")));
	singleComponents.push_back(dynamic_pointer_cast<Component>(std::make_shared<MainCameraComponent>()));
	if(FPS_COUNTER) singleComponents.push_back(dynamic_pointer_cast<Component>(std::make_shared<FPSCounterComponent>()));
	vector<std::string> faces
	{
		"resources/skybox/right.jpg",
		"resources/skybox/left.jpg",
		"resources/skybox/top.jpg",
		"resources/skybox/bottom.jpg",
		"resources/skybox/back.jpg",
		"resources/skybox/front.jpg",
	};
	//vector<std::string> faces
	//{
	//	"resources/mp_crimimpact/criminal-impact_rt.tga",
	//	"resources/mp_crimimpact/criminal-impact_lf.tga",
	//	"resources/mp_crimimpact/criminal-impact_up.tga",
	//	"resources/mp_crimimpact/criminal-impact_dn.tga",
	//	"resources/mp_crimimpact/criminal-impact_bk.tga",
	//	"resources/mp_crimimpact/criminal-impact_ft.tga",
	//};
	//vector<std::string> faces
	//{
	//	"resources/hw_crater/craterlake_rt.tga",
	//	"resources/hw_crater/craterlake_lf.tga",
	//	"resources/hw_crater/craterlake_up.tga",
	//	"resources/hw_crater/craterlake_dn.tga",
	//	"resources/hw_crater/craterlake_bk.tga",
	//	"resources/hw_crater/craterlake_ft.tga",
	//};
	singleComponents.push_back(dynamic_pointer_cast<Component>(std::make_shared<SkyboxComponent>(faces)));
	singleComponents.push_back(dynamic_pointer_cast<Component>(std::make_shared<SkyboxShaderComponent>("shaders/cubeMapShader.vert", "shaders/cubeMapShader.frag")));
}

void EntityAdmin::CreateLightEntity(float x, float y, float z)
{
	CreateEntityTemplate(resMan.CreateComponent(TransformComponent(glm::vec3(x, y, z))), resMan.CreateComponent(PointLightComponent()));
	//CreateEntityTemplate(make_shared<TransformComponent>(glm::vec3(x, y, z)), make_shared<PointLightComponent>());
}

void EntityAdmin::CreateModelEntity(float x, float y, float z, std::string path)
{
	CreateEntityTemplate(make_shared<TransformComponent>(glm::vec3(x, y, z)), make_shared<ModelComponent>(path));
}

void EntityAdmin::InitEntities()
{
	for (const auto& cubePos : cubePositions)
	{
		CreateModelEntity(cubePos.x, cubePos.y, cubePos.z, "resources/nanosuit/nanosuit.obj");
	}
	CreateLightEntity(-5.0f, 0.0f, 0.0f);
	CreateLightEntity(0.0f, 2.0f, -2.0f);
	CreateLightEntity(-1.0f, 1.0f, -5.0f);

	auto cam = CreateEntityTemplate(resMan.CreateComponent(TransformComponent()), resMan.CreateComponent(PerspectiveCameraComponent()));
	auto mainCam = GetSingle<MainCameraComponent>();
	mainCam->MainCamera = CameraTuple::FromEntity(cam);
}

vector<shared_ptr<Shader>> EntityAdmin::GetShaders()
{
	vector<std::shared_ptr<Shader>> res;
	for (const auto& component : singleComponents)
	{
		if (auto test = std::dynamic_pointer_cast<Shader>(component)) {
			res.push_back(test);
		}
	}
	return res;
}

void EntityAdmin::Update(float timestep)
{
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

std::vector<std::shared_ptr<RenderTuple>> EntityAdmin::GetRenderTuples()
{
	return RenderTuple::GetRenderTuples(entities);
}
std::vector<std::shared_ptr<PointLightTuple>> EntityAdmin::GetPointLightTuples()
{
	return PointLightTuple::GetPointLightTuples(entities);
}

std::shared_ptr<CameraTuple> EntityAdmin::GetMainCamera()
{
	return GetSingle<MainCameraComponent>()->MainCamera;
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
