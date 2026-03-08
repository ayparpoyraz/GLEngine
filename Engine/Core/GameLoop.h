#pragma once
#include "../renderEngine/Display.h"
#include "../models/RawModel.h"
#include "../renderEngine/Loader.h"
#include "../renderEngine/Renderer.h"



class GameLoop {
public:
    void run(GLFWwindow* window, RawModel& model);

private:
    Renderer renderer;
    void processInput(GLFWwindow* window);
};