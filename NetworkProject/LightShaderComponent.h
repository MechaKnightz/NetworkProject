#pragma once
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class LightShaderComponent : public Shader
{
public:
	LightShaderComponent(const std::string vertexPath, const std::string fragmentPath) : Shader(vertexPath, fragmentPath)
	{

		projectionMatrixLocation = glGetUniformLocation(ID, "projection");
		viewMatrixLocation = glGetUniformLocation(ID, "view");
		modelMatrixLocation = glGetUniformLocation(ID, "model");

		viewPosLocation = glGetUniformLocation(ID, "viewPos");

		shininessLocation = glGetUniformLocation(ID, "material.shininess");

		//objectColorLocation = glGetUniformLocation(ID, "objectColor");
		//lightColorLocation = glGetUniformLocation(ID, "lightColor" );
		lightPositionLocation = glGetUniformLocation(ID, "light.position");
		lightDirectionLocation = glGetUniformLocation(ID, "light.direction");

		lightAmbientLocation = glGetUniformLocation(ID, "light.ambient");
		lightDiffuseLocation = glGetUniformLocation(ID, "light.diffuse");
		lightSpecularLocation = glGetUniformLocation(ID, "light.specular");

		lightConstantLocation = glGetUniformLocation(ID, "light.constant");
		lightLinearLocation = glGetUniformLocation(ID, "light.linear");
		lightQuadraticLocation = glGetUniformLocation(ID, "light.quadratic");
	}
	void SetProjectionMatrix(const glm::mat4& matrix)
	{
		glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(matrix));
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

	void SetLightPosition(const glm::vec3& vec)
	{
		glUniform3fv(lightPositionLocation, 1, &vec[0]);
	}
	void SetLightDirection(const glm::vec3& vec)
	{
		glUniform3fv(lightDirectionLocation, 1, &vec[0]);
	}

	void SetLightAmbient(const glm::vec3& vec)
	{
		glUniform3fv(lightAmbientLocation, 1, &vec[0]);
	}
	void SetLightDiffuse(const glm::vec3& vec)
	{
		glUniform3fv(lightDiffuseLocation, 1, &vec[0]);
	}
	void SetLightSpecular(const glm::vec3& vec)
	{
		glUniform3fv(lightSpecularLocation, 1, &vec[0]);
	}
	void SetLightConstant(const float& value)
	{
		glUniform1f(lightConstantLocation, value);
	}
	void SetLightLinear(const float& value)
	{
		glUniform1f(lightLinearLocation, value);
	}
	void SetLightQuadratic(const float& value)
	{
		glUniform1f(lightQuadraticLocation, value);
	}
private:
	int32_t projectionMatrixLocation;
	int32_t viewMatrixLocation;
	int32_t modelMatrixLocation;

	int32_t viewPosLocation;

	int32_t shininessLocation;

	int32_t lightPositionLocation;
	int32_t lightDirectionLocation;
	//uint32_t objectColorLocation;
	//uint32_t lightColorLocation;
	int32_t lightAmbientLocation;
	int32_t lightDiffuseLocation;
	int32_t lightSpecularLocation;

	int32_t lightConstantLocation;
	int32_t lightLinearLocation;
	int32_t lightQuadraticLocation;
};