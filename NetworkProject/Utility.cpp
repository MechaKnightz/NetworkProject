#include "Utility.h"
#include <chrono>

int64_t Utility::GetTime()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}
