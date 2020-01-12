#include "RenderSystem.h"
#include <glad\glad.h>
#include <iostream>
#include "EntityAdmin.h"
#include "ShaderComponent.h"

float vertices[] = {
    // positions         // colors
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
};

unsigned int indices[] = {  
    0, 1, 3,
    1, 2, 3
};

RenderSystem::RenderSystem(EntityAdmin* admin) : System(admin)
{
    auto tuple = this->admin->GetShaderTuple();
}

void RenderSystem::Update(float timestep)
{
    auto tuple = admin->GetShaderTuple();
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.

    tuple->shaderComponent->VAO = VAO;
    tuple->shaderComponent->VBO = VBO;
    tuple->shaderComponent->EBO = EBO;

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void RenderSystem::Draw(float interp) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    auto tuple = this->admin->GetShaderTuple();

    glUseProgram(tuple->shaderComponent->ID);
    glBindVertexArray(tuple->shaderComponent->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
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

