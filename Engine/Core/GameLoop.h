#pragma once
#include <glm/glm.hpp>
#include "../Display/Display.h"
#include "../models/RawModel.h"
#include "../renderEngine/Renderer.h"
#include "../shaders/StaticShader.h"
#include "../Math/Math.h"

class GameLoop {
public:
    void run(GLFWwindow* window, RawModel& model,
        glm::vec3 position, glm::vec3 rotation, float scale);

private:
    Renderer renderer;
    StaticShader shader;
    void processInput(GLFWwindow* window);
};