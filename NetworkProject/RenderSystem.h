#pragma once
#include "System.h"
#include <string>

class RenderSystem : public System
{
public:
	RenderSystem(EntityAdmin* admin);
	void Update(float timestep);
	void Draw(float interp);

	~RenderSystem();
private:
	void SetFloat(std::string name, float value);
};

