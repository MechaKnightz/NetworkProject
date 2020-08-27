#pragma once
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class LightShaderComponent : public Shader
{
public:
	LightShaderComponent(const std::string vertexPath, const std::string fragmentPath) : Shader(vertexPath, fragmentPath)
	{
		viewMatrixLocation = glGetUniformLocation(ID, "view");
		modelMatrixLocation = glGetUniformLocation(ID, "model");

		viewPosLocation = glGetUniformLocation(ID, "viewPos");

		shininessLocation = glGetUniformLocation(ID, "material.shininess");

		glUseProgram(ID);

		glUniform1i(glGetUniformLocation(ID, "material.diffuse"), 0);
		glUniform1i(glGetUniformLocation(ID, "material.ambient"), 1);
		glUniform1i(glGetUniformLocation(ID, "material.specular"), 2);
	}
	void SetViewMatrix(const glm::mat4& matrix)
	{
		glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(matrix));
	}
	void SetModelMatrix(const glm::mat4& matrix)
	{
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	//void SetObjectColor(const glm::vec3& vec)
	//{
	//	glUniform3fv(objectColorLocation, 1, &vec[0]);
	//}
	//void SetLightColor(const glm::vec3& vec)
	//{
	//	glUniform3fv(lightColorLocation, 1, &vec[0]);
	//}
	void SetViewPosition(const glm::vec3& vec)
	{
		glUniform3fv(viewPosLocation, 1, &vec[0]);
	}
	void SetShininess(const float& value)
	{
		glUniform1f(shininessLocation, value);
	}
	void SetLights(const std::vector<std::shared_ptr<PointLightTuple>>& lights)
	{
		//todo
	}
private:
	int32_t viewMatrixLocation;
	int32_t modelMatrixLocation;

	int32_t viewPosLocation;

	int32_t shininessLocation;
};