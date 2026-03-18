#pragma once

#include <glm/glm.hpp>
#include "../../Display/Display.h"
#include "../../models/RawModel.h"
#include "../../Renderer/Renderer.h"
#include "../../Shaders/StaticShader.h"
#include "../../Math/Math.h"
#include "../../Entities/Entity.h"
#include "../../Camera/Camera.h"
#include "../../Camera/FreeCamera.h"
#include "../../OBJLoader/OBJLoader.h"
#include "../../Renderer/Loader/Loader.h"
#include <vector>


enum class CameraMode {
    Free,
    FPS,
    Orbit
};

class Editor {
    CameraMode currentMode = CameraMode::Free;
public:
    Editor() : camera(glm::vec3(0.0f, 0.0f, 3.0f)) {}
    bool run(GLFWwindow* window, std::vector<Entity>& entities /*RawModel& defaultModel*/);


private:
    Loader loader;
    std::vector<std::string> modelFiles;
    std::vector<std::string> textureFiles;
    void scanResources();
    Renderer renderer;
    StaticShader shader;
    FreeCamera camera;
    //void processInput(GLFWwindow* window);
    void applyEditorTheme();
    bool isMenuVisible = true;
    bool isStarted = false;
};