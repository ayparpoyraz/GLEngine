#pragma once
#include "../renderEngine/Display.h"
#include "../models/RawModel.h"
#include "../renderEngine/Loader.h"
#include "../renderEngine/Renderer.h"
#include "../shaders/StaticShader.h"



class GameLoop {
public:
    void run(GLFWwindow* window, RawModel& model);

private:
    Renderer renderer;
    StaticShader shader;
    void processInput(GLFWwindow* window);
};