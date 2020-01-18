#pragma once
#include <tuple>
#include "TransformComponent.h"
#include "ModelComponent.h"
#include <memory>

class TestTuple : public std::tuple<std::shared_ptr<TransformComponent>, std::shared_ptr<TransformComponent>>
{
public: 
	std::shared_ptr<TransformComponent> GetTransformComponent()
	{
		return std::get<std::shared_ptr<TransformComponent>>(*this);
	}
};