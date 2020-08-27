#pragma once
#include "Shader.h"

class SkyboxShaderComponent : public Shader
{
public:
	SkyboxShaderComponent(const std::string vertexPath, const std::string fragmentPath) : Shader(vertexPath, fragmentPath)
	{
		viewMatrixLocation = glGetUniformLocation(ID, "view");
	}
	void SetViewMatrix(const glm::mat4& matrix)
	{
		glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(matrix));
	}
private:
	int32_t viewMatrixLocation;
};