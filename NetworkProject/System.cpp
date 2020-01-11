#include "System.h"

void System::Update(float timestep)
{
}

void System::Draw(float interp)
{
}

System::System(EntityAdmin* admin)
{
	this->admin = admin;
}
