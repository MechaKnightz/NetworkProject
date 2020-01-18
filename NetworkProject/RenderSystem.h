#pragma once
#include "System.h"
#include <string>

#include "ModelComponent.h"
#include "TransformComponent.h"

class RenderSystem : public System
{
public:
	RenderSystem(EntityAdmin* admin);
	void Update(float timestep);
	void Draw(float interp);

	~RenderSystem();
private:
	void SetFloat(std::string name, float value);
	void SetMat4(std::string name, glm::mat4 value);
};

