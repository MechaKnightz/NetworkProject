#pragma once
#include <cstdint>
class ModelComponent {
public:
	uint32_t VAO;
	uint32_t VBO;
	uint32_t EBO;

	uint32_t Texture;
	uint32_t Texture2;

	ModelComponent()
	{

	}
};