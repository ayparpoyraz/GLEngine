#pragma once
#include <glm/glm.hpp>
#include "../Display/Display.h"
#include "../models/RawModel.h"
#include "../renderEngine/Renderer.h"
#include "../shaders/StaticShader.h"
#include "../Math/Math.h"
#include "../Entities/Entity.h"
#include <vector>

class GameLoop {
public:
    void run(GLFWwindow* window, std::vector<Entity>& entities);

private:
    Renderer renderer;
    StaticShader shader;
    void processInput(GLFWwindow* window);
};