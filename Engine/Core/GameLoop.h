#pragma once
#include <glm/glm.hpp>
#include "../Display/Display.h"
#include "../models/RawModel.h"
#include "../Renderer/Renderer.h"
#include "../Shaders/StaticShader.h"
#include "../Math/Math.h"
#include "../Entities/Entity.h"
#include "../Camera/master/masterCamera.h"
#include "../Skybox/Skybox.h"
#include <vector>

class GameLoop {
public:
    GameLoop() : camera(glm::vec3(0.0f, 0.0f, 3.0f)) {}
    void run(GLFWwindow* window, std::vector<Entity>& entities);

private:
    Renderer renderer;
    StaticShader shader;
    masterCamera camera;

    void processInput(GLFWwindow* window);

};  