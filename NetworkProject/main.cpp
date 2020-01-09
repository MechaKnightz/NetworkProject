#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "main.h"
#include <iostream>
#include <boost/regex.hpp>
#include "Engine.h"

int WINDOW_WIDTH = 1600;
int WINDOW_HEIGHT = 900;
std::string WINDOW_NAME = "NetworkProject";

void initGLFW();

void initGLFW()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

int main()
{
    initGLFW();

    eng::Engine engine(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME);
    engine.run();
    return 0;
}