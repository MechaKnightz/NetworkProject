#pragma once
#include <memory>

class EntityAdmin;
class System
{
public:
	virtual void Update(float timestep);
	virtual void Draw(float interp);

	System(EntityAdmin* admin);
protected:
	EntityAdmin* admin;
};

