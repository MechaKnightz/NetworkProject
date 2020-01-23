#pragma once
#include "LightComponent.h"
#include <glm/glm.hpp>

class PointLightComponent : public LightComponent
{
public:
    PointLightComponent()
    {
        glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

        Diffuse = lightColor * glm::vec3(0.5f);
        Ambient = lightColor * glm::vec3(0.1f);
        Specular = lightColor * glm::vec3(1.0f);

        Constant = 1.0f;
        Linear = 0.09;
        Quadratic = 0.032;
    }
    float Constant;
    float Linear;
    float Quadratic;

    glm::vec3 Ambient;
    glm::vec3 Diffuse;
    glm::vec3 Specular;
};

