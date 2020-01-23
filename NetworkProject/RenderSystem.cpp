#include "RenderSystem.h"
#include <glad/glad.h>
#include <iostream>
#include "EntityAdmin.h"
#include "ShaderComponent.h"
#include "LightComponent.h"
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include "CameraComponent.h"
#include "LightTuple.h"
#include "LightShaderComponent.h"
#include "Utility.h"
#include "PointLightComponent.h"

RenderSystem::RenderSystem(EntityAdmin* admin) : System(admin)
{
    auto lightShaderComponent = admin->GetSingle<LightShaderComponent>();

    stbi_set_flip_vertically_on_load(true);

    glUseProgram(lightShaderComponent->ID);

    glUniform1i(glGetUniformLocation(lightShaderComponent->ID, "material.diffuse"), 0);
    glUniform1i(glGetUniformLocation(lightShaderComponent->ID, "material.ambient"), 1);
    glUniform1i(glGetUniformLocation(lightShaderComponent->ID, "material.specular"), 2);

    glEnable(GL_DEPTH_TEST);
}

void RenderSystem::Update(float timestep)
{
}


void setFloat(int id, const std::string& name, float value)
{
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void setVec3(int id, const std::string& name, const glm::vec3& value)
{
    glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
}

void RenderSystem::Draw(float interp) {
    auto cameraComponent = admin->GetSingle<CameraComponent>();
    auto lightShaderComponent = admin->GetSingle<LightShaderComponent>();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(90.0f), 1600.0f / 900.0f, 0.1f, 100.0f);

    //start

    glUseProgram(lightShaderComponent->ID);
    //lightShaderComponent->SetObjectColor(glm::vec3(1.0f, 0.5f, 0.31f));
    //lightShaderComponent->SetLightColor(glm::vec3(1.0f, 1.0f, 1.0f));
    lightShaderComponent->SetViewPosition(cameraComponent->Position);
    lightShaderComponent->SetShininess(32.0f);

    //lightShaderComponent->SetLightDirection(glm::vec3(-0.2f, -1.0f, -0.3f));

    lightShaderComponent->SetProjectionMatrix(projection);
    lightShaderComponent->SetViewMatrix(cameraComponent->GetViewMatrix());

    int i = 0;
    auto tuples = admin->GetPointLightTuples();
    glUniform1i(glGetUniformLocation(lightShaderComponent->ID, "nrOfPointLights"), tuples.size());
    for (auto const& tuple : tuples)
    {
        setVec3(lightShaderComponent->ID, "pointLights[" + std::to_string(i) + "].position", tuple->transformComponent->Position);
        setVec3(lightShaderComponent->ID, "pointLights[" + std::to_string(i) + "].ambient", tuple->pointLightComponent->Ambient);
        setVec3(lightShaderComponent->ID, "pointLights[" + std::to_string(i) + "].diffuse", tuple->pointLightComponent->Diffuse);
        setVec3(lightShaderComponent->ID, "pointLights[" + std::to_string(i) + "].specular", tuple->pointLightComponent->Specular);

        setFloat(lightShaderComponent->ID, "pointLights[" + std::to_string(i) + "].constant", tuple->pointLightComponent->Constant);
        setFloat(lightShaderComponent->ID, "pointLights[" + std::to_string(i) + "].linear", tuple->pointLightComponent->Linear);
        setFloat(lightShaderComponent->ID, "pointLights[" + std::to_string(i) + "].quadratic", tuple->pointLightComponent->Quadratic);
        i++;
    }

    int vao;
    for (auto const& tuple : admin->GetRenderTuples())
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tuple->modelComponent->Texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, tuple->modelComponent->Texture2);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, tuple->modelComponent->Texture3);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, tuple->transformComponent->Position);
        model = glm::rotate(model, glm::radians((float)glfwGetTime() * 25.0f), glm::vec3(1.0f, 0.3f, 0.5f));

        lightShaderComponent->SetModelMatrix(model);

        glBindVertexArray(tuple->modelComponent->VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        vao = tuple->modelComponent->VAO;
    }
    //end
    auto shaderComponent = admin->GetSingle<ShaderComponent>();
    glUseProgram(shaderComponent->ID);

    shaderComponent->SetProjectionMatrix(projection);
    shaderComponent->SetViewMatrix(cameraComponent->GetViewMatrix());

    for (auto const& tuple : admin->GetPointLightTuples())
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, tuple->transformComponent->Position);
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));

        shaderComponent->SetModelMatrix(model);

        glBindVertexArray(tuple->pointLightComponent->VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}
 
RenderSystem::~RenderSystem()
{
    //auto shaderComponent = admin->GetSingle<ShaderComponent>();
    //glDeleteVertexArrays(1, &shaderComponent->VAO);
    //glDeleteBuffers(1, &shaderComponent->VBO);
    //glDeleteBuffers(1, &shaderComponent->EBO);
}

void RenderSystem::SetFloat(std::string name, float value)
{
    auto shaderComponent = admin->GetSingle<ShaderComponent>();
    glUniform1f(glGetUniformLocation(shaderComponent->ID, name.c_str()), value);
}

void RenderSystem::SetMat4(std::string name, glm::mat4 value)
{
    auto shaderComponent = admin->GetSingle<ShaderComponent>();
    glUniformMatrix4fv(glGetUniformLocation(shaderComponent->ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}


