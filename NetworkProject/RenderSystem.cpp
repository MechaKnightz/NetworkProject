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
#include "LightShaderComponent.h"
#include "Utility.h"
#include "PointLightComponent.h"
#include "SkyboxComponent.h"
#include "SkyboxShaderComponent.h"
#include "WindowComponent.h"
#include "MainCameraComponent.h"
#include "CameraTuple.h"
#include "CameraComponent.h"

RenderSystem::RenderSystem(EntityAdmin* admin) : System(admin)
{
    stbi_set_flip_vertically_on_load(true);

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

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    DrawModels();
    DrawLamps();
    DrawSkybox();
}
 
RenderSystem::~RenderSystem()
{
    //auto shaderComponent = admin->GetSingle<ShaderComponent>();
    //glDeleteVertexArrays(1, &shaderComponent->VAO);
    //glDeleteBuffers(1, &shaderComponent->VBO);
    //glDeleteBuffers(1, &shaderComponent->EBO);
}

void RenderSystem::DrawSkybox()
{
    auto skyboxComponent = admin->GetSingle<SkyboxComponent>();
    auto skyboxShaderComponent = admin->GetSingle<SkyboxShaderComponent>();
    auto cameraComponent = admin->GetMainCamera();
    auto windowComponent = admin->GetSingle<WindowComponent>();


    glDepthFunc(GL_LEQUAL);
    glUseProgram(skyboxShaderComponent->ID);

    //skyboxShaderComponent->SetProjectionMatrix(windowComponent->ProjectionMatrix);
    skyboxShaderComponent->SetViewMatrix(glm::mat4(glm::mat3(cameraComponent->Camera->ViewMatrix)));

    glBindVertexArray(skyboxComponent->VAO);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxComponent->Texture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDepthMask(GL_TRUE);
}

void RenderSystem::DrawModels()
{
    auto cameraComponent = admin->GetMainCamera();
    auto lightShaderComponent = admin->GetSingle<LightShaderComponent>();
    auto windowComponent = admin->GetSingle<WindowComponent>();

    glUseProgram(lightShaderComponent->ID);
    //lightShaderComponent->SetObjectColor(glm::vec3(1.0f, 0.5f, 0.31f));
    //lightShaderComponent->SetLightColor(glm::vec3(1.0f, 1.0f, 1.0f));
    lightShaderComponent->SetViewPosition(cameraComponent->Transform->Position);
    lightShaderComponent->SetShininess(32.0f);

    //lightShaderComponent->SetLightDirection(glm::vec3(-0.2f, -1.0f, -0.3f));

    int i = 0;
    auto tuples = admin->GetPointLightTuples();
    glUniform1i(glGetUniformLocation(lightShaderComponent->ID, "nrOfPointLights"), tuples.size());
    for (auto const& tuple : tuples)
    {
        setVec3(lightShaderComponent->ID, "pointLights[" + std::to_string(i) + "].position", tuple->Transform->Position);
        setVec3(lightShaderComponent->ID, "pointLights[" + std::to_string(i) + "].ambient", tuple->PointLight->Ambient);
        setVec3(lightShaderComponent->ID, "pointLights[" + std::to_string(i) + "].diffuse", tuple->PointLight->Diffuse);
        setVec3(lightShaderComponent->ID, "pointLights[" + std::to_string(i) + "].specular", tuple->PointLight->Specular);

        setFloat(lightShaderComponent->ID, "pointLights[" + std::to_string(i) + "].constant", tuple->PointLight->Constant);
        setFloat(lightShaderComponent->ID, "pointLights[" + std::to_string(i) + "].linear", tuple->PointLight->Linear);
        setFloat(lightShaderComponent->ID, "pointLights[" + std::to_string(i) + "].quadratic", tuple->PointLight->Quadratic);
        i++;
    }

    //lightShaderComponent->SetProjectionMatrix(windowComponent->ProjectionMatrix);
    lightShaderComponent->SetViewMatrix(cameraComponent->Camera->ViewMatrix);
    for (const auto& tuple : admin->GetRenderTuples())
    {

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, tuple->Transform->Position);
        model = glm::rotate(model, glm::radians((float)glfwGetTime() * 25.0f), glm::vec3(1.0f, 0.3f, 0.5f));

        lightShaderComponent->SetModelMatrix(model);

        for (const auto& mesh : tuple->Model->Meshes)
        {
            // bind appropriate textures
            unsigned int diffuseNr = 1;
            unsigned int specularNr = 1;
            unsigned int normalNr = 1;
            unsigned int heightNr = 1;
            for (unsigned int i = 0; i < mesh.textures.size(); i++)
            {
                glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
                // retrieve texture number (the N in diffuse_textureN)
                std::string number;
                std::string name = mesh.textures[i].type;
                if (name == "texture_diffuse")
                    number = std::to_string(diffuseNr++);
                else if (name == "texture_specular")
                    number = std::to_string(specularNr++); // transfer unsigned int to stream
                else if (name == "texture_normal")
                    number = std::to_string(normalNr++); // transfer unsigned int to stream
                else if (name == "texture_height")
                    number = std::to_string(heightNr++); // transfer unsigned int to stream

                // now set the sampler to the correct texture unit
                glUniform1i(glGetUniformLocation(lightShaderComponent->ID, (name + number).c_str()), i);
                // and finally bind the texture
                glBindTexture(GL_TEXTURE_2D, mesh.textures[i].id);
            }

            // draw mesh
            glBindVertexArray(mesh.VAO);
            glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);

            // always good practice to set everything back to defaults once configured.
            glActiveTexture(GL_TEXTURE0);
        }
    }
}

void RenderSystem::DrawLamps()
{
    auto cameraComponent = admin->GetMainCamera();
    auto shaderComponent = admin->GetSingle<ShaderComponent>();
    auto windowComponent = admin->GetSingle<WindowComponent>();

    glUseProgram(shaderComponent->ID);

    //shaderComponent->SetProjectionMatrix(windowComponent->ProjectionMatrix);
    shaderComponent->SetViewMatrix(cameraComponent->Camera->ViewMatrix);
    for (auto const& tuple : admin->GetPointLightTuples())
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, tuple->Transform->Position);
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));

        shaderComponent->SetModelMatrix(model);

        glBindVertexArray(tuple->PointLight->VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}


