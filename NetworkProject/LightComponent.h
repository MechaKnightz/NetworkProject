#pragma once
#include "Component.h"
#include <cstdint>
#include <glad\glad.h>

class LightComponent : public Component
{
public:
	uint32_t VAO;
	uint32_t VBO;

	LightComponent() {

        float vertices[] = {
            -0.5f, -0.5f, -0.5f, 
             0.5f, -0.5f, -0.5f,  
             0.5f,  0.5f, -0.5f,  
             0.5f,  0.5f, -0.5f, 
            -0.5f,  0.5f, -0.5f,  
            -0.5f, -0.5f, -0.5f,  

            -0.5f, -0.5f,  0.5f, 
             0.5f, -0.5f,  0.5f,  
             0.5f,  0.5f,  0.5f,  
             0.5f,  0.5f,  0.5f,  
            -0.5f,  0.5f,  0.5f, 
            -0.5f, -0.5f,  0.5f,  

            -0.5f,  0.5f,  0.5f,  
            -0.5f,  0.5f, -0.5f,  
            -0.5f, -0.5f, -0.5f, 
            -0.5f, -0.5f, -0.5f,  
            -0.5f, -0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,  

             0.5f,  0.5f,  0.5f,  
             0.5f,  0.5f, -0.5f, 
             0.5f, -0.5f, -0.5f,  
             0.5f, -0.5f, -0.5f, 
             0.5f, -0.5f,  0.5f, 
             0.5f,  0.5f,  0.5f,  

            -0.5f, -0.5f, -0.5f, 
             0.5f, -0.5f, -0.5f, 
             0.5f, -0.5f,  0.5f,  
             0.5f, -0.5f,  0.5f, 
            -0.5f, -0.5f,  0.5f, 
            -0.5f, -0.5f, -0.5f, 

            -0.5f,  0.5f, -0.5f, 
             0.5f,  0.5f, -0.5f, 
             0.5f,  0.5f,  0.5f, 
             0.5f,  0.5f,  0.5f, 
            -0.5f,  0.5f,  0.5f, 
            -0.5f,  0.5f, -0.5f,
        };

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
	}
};