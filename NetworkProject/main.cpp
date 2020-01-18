#include "Engine.h"
#include <iostream>
#include <memory>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main()
{
	std::unique_ptr<Engine> engine = std::make_unique<Engine>();
    engine->Initialize();
    engine->Run();
    return 0;
}