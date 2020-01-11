#pragma once
#include "Component.h"

class ShaderComponent : public Component
{
public:
	uint32_t vertexShader;
	uint32_t fragmentShader;
	uint32_t shaderProgram;

	uint32_t VAO;
	uint32_t VBO;
	uint32_t EBO;
};