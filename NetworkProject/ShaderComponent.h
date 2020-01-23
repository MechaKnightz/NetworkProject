#pragma once
#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <glad\glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class ShaderComponent : public Shader
{
public:
    ShaderComponent(const std::string vertexPath, const std::string fragmentPath) : Shader(vertexPath, fragmentPath)
	{
        projectionMatrixLocation = glGetUniformLocation(ID, "projection");
        viewMatrixLocation = glGetUniformLocation(ID, "view");
        modelMatrixLocation = glGetUniformLocation(ID, "model");
	}
    void SetProjectionMatrix(const glm::mat4& matrix)
    {
        glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(matrix));
    }
    void SetViewMatrix(const glm::mat4& matrix)
    {
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(matrix));
    }
    void SetModelMatrix(const glm::mat4& const matrix)
    {
        glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(matrix));
    }
private:
    uint32_t projectionMatrixLocation;
    uint32_t viewMatrixLocation;
    uint32_t modelMatrixLocation;
};