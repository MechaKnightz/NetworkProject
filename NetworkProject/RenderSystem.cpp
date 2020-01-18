#include "RenderSystem.h"
#include <glad/glad.h>
#include <iostream>
#include "EntityAdmin.h"
#include "ShaderComponent.h"
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include "CameraComponent.h"

RenderSystem::RenderSystem(EntityAdmin* admin) : System(admin)
{
    auto shaderComponent = admin->GetSingle<ShaderComponent>();

    stbi_set_flip_vertically_on_load(true);

    glUseProgram(shaderComponent->ID);

    glUniform1i(glGetUniformLocation(shaderComponent->ID, "texture1"), 0);
    glUniform1i(glGetUniformLocation(shaderComponent->ID, "texture2"), 1);

    glEnable(GL_DEPTH_TEST);
}

void RenderSystem::Update(float timestep)
{
    auto shaderComponent = admin->GetSingle<ShaderComponent>();
    glUniform1f(glGetUniformLocation(shaderComponent->ID, "mixValue"), shaderComponent->MixValue);

    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    projection = glm::perspective(glm::radians(90.0f), 1600.0f / 900.0f, 0.1f, 100.0f);

    shaderComponent->SetProjectionMatrix(projection);
}

void RenderSystem::Draw(float interp) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    auto shaderComponent = admin->GetSingle<ShaderComponent>();
    auto cameraComponent = admin->GetSingle<CameraComponent>();

    glUseProgram(shaderComponent->ID);

    shaderComponent->SetViewMatrix(cameraComponent->GetViewMatrix());

    auto tuples = admin->GetRenderTuple();
    for (auto const& tuple : tuples)
    {
        glBindVertexArray(tuple->modelComponent->VAO);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tuple->modelComponent->Texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, tuple->modelComponent->Texture2);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, tuple->transformComponent->Position);
        model = glm::rotate(model, glm::radians((float)glfwGetTime() * 25.0f), glm::vec3(1.0f, 0.3f, 0.5f));

        shaderComponent->SetModelMatrix(model);

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


