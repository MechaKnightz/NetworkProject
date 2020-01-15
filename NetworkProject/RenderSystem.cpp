#include "RenderSystem.h"
#include <glad/glad.h>
#include <iostream>
#include "EntityAdmin.h"
#include "ShaderComponent.h"
#include "stb_image.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include "CameraComponent.h"

float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};

RenderSystem::RenderSystem(EntityAdmin* admin) : System(admin)
{
    auto tuple = admin->GetShaderTuple();
    glGenVertexArrays(1, &tuple->shaderComponent->VAO);
    glGenBuffers(1, &tuple->shaderComponent->VBO);
    //glGenBuffers(1, &tuple->shaderComponent->EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(tuple->shaderComponent->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, tuple->shaderComponent->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tuple->shaderComponent->EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //load texture
    glGenTextures(1, &tuple->shaderComponent->Texture);
    glBindTexture(GL_TEXTURE_2D, tuple->shaderComponent->Texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    int width, height, nrChannels;

    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("resources/container.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    glGenTextures(1, &tuple->shaderComponent->Texture2);
    glBindTexture(GL_TEXTURE_2D, tuple->shaderComponent->Texture2);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    data = stbi_load("resources/bananas.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    glUseProgram(tuple->shaderComponent->ID);

    glUniform1i(glGetUniformLocation(tuple->shaderComponent->ID, "texture1"), 0);
    glUniform1i(glGetUniformLocation(tuple->shaderComponent->ID, "texture2"), 1);

    tuple->shaderComponent->ProjectionMatrixLocation = glGetUniformLocation(tuple->shaderComponent->ID, "projection");
    tuple->shaderComponent->ViewMatrixLocation = glGetUniformLocation(tuple->shaderComponent->ID, "view");
    tuple->shaderComponent->ModelMatrixLocation = glGetUniformLocation(tuple->shaderComponent->ID, "model");

    glEnable(GL_DEPTH_TEST);
}

void RenderSystem::Update(float timestep)
{

    auto tuple = admin->GetShaderTuple();
    glUniform1f(glGetUniformLocation(tuple->shaderComponent->ID, "mixValue"), tuple->shaderComponent->mixValue);

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    projection = glm::perspective(glm::radians(90.0f), 1600.0f / 900.0f, 0.1f, 100.0f);

    glUniformMatrix4fv(tuple->shaderComponent->ModelMatrixLocation, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(tuple->shaderComponent->ViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(tuple->shaderComponent->ProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projection));
}

void RenderSystem::Draw(float interp) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    auto tuple = this->admin->GetShaderTuple();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tuple->shaderComponent->Texture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, tuple->shaderComponent->Texture2);

    glUseProgram(tuple->shaderComponent->ID);
    glBindVertexArray(tuple->shaderComponent->VAO);

    for (unsigned int i = 0; i < 10; i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        float angle = 20.0f * i;
        if (i % 3 == 0)  // every 3rd iteration (including the first) we set the angle using GLFW's time function.
            angle = glfwGetTime() * 25.0f;
        
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        model = glm::scale(model, glm::vec3(2, 2, 2));
        glUniformMatrix4fv(tuple->shaderComponent->ModelMatrixLocation, 1, GL_FALSE, glm::value_ptr(model));

        glm::mat4 view = tuple->cameraComponent->GetViewMatrix();
        glUniformMatrix4fv(tuple->shaderComponent->ViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(view));

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

RenderSystem::~RenderSystem()
{
    auto tuple = this->admin->GetShaderTuple();
    //glDeleteVertexArrays(1, &tuple->shaderComponent->VAO);
    //glDeleteBuffers(1, &tuple->shaderComponent->VBO);
    //glDeleteBuffers(1, &tuple->shaderComponent->EBO);
}

void RenderSystem::SetFloat(std::string name, float value)
{
    auto tuple = this->admin->GetShaderTuple();
    glUniform1f(glGetUniformLocation(tuple->shaderComponent->ID, name.c_str()), value);
}

