#pragma once
#include "Component.h"
#include <memory>
#include "CameraComponent.h"
#include "CameraTuple.h"

class MainCameraComponent : public Component
{
public:
    std::shared_ptr<CameraTuple> MainCamera;
};

