#pragma once
#include <memory>

class EntityAdmin;
class System
{
public:
	virtual void Update(float timestep);

	System(EntityAdmin* admin);
protected:
	EntityAdmin* admin;
};

