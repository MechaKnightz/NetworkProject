#include "FPSCounterSystem.h"
#include "EntityAdmin.h"
#include "FPSCounterComponent.h"
#include "Utility.h"

FPSCounterSystem::FPSCounterSystem(EntityAdmin* admin) : System(admin)
{

}

void FPSCounterSystem::Draw(float interp)
{
	auto fpsComponent = admin->GetSingle<FPSCounterComponent>();

	fpsComponent->Counter++;
	if (fpsComponent->PreviousTime + 1000 < Utility::GetTime())
	{
		std::cout << fpsComponent->Counter << std::endl;
		fpsComponent->Counter = 0;
		fpsComponent->PreviousTime = Utility::GetTime();
	}
}
