#pragma once
#include <glm\ext\matrix_float4x4.hpp>
#include "Component.h"

class CameraComponent : public Component {
public:
    glm::mat4x4 ViewMatrix = glm::mat4x4();
};