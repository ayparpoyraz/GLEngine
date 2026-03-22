#pragma once

#include <glm/glm.hpp>
#include "../../Display/Display.h"
#include "../../models/RawModel.h"
#include "../../Renderer/Renderer.h"
#include "../../Shaders/StaticShader.h"
#include "../../Math/Math.h"
#include "../../Entities/Entity.h"
#include "../../Camera/Camera.h"
//#include "../../Camera/FreeCamera.h"
//#include "../../Camera/OrbitCamera.h"
#include "../../Camera/master/masterCamera.h"
#include "../../OBJLoader/OBJLoader.h"
#include "../../Renderer/Loader/Loader.h"
#include "../../Skybox/Skybox.h"
#include <vector>


enum class CameraMode {
    Free,
    FPS,
    Orbit,
    masterCamera
};

class Editor {
    CameraMode currentMode = CameraMode::masterCamera;
public:
    Editor() : camera(glm::vec3(0.0f, 0.0f, 5.0f)) {}
    bool run(GLFWwindow* window, std::vector<Entity>& entities /*RawModel& defaultModel*/);


private:
    Loader loader;
    std::vector<std::string> modelFiles;
    std::vector<std::string> textureFiles;
    void scanResources();
    Renderer renderer;
    StaticShader shader;
    masterCamera camera;
    Skybox skybox;
    //OrbitCamera orbitCamera{ glm::vec3(0.0f), 5.0f };
    
    //void processInput(GLFWwindow* window);
    void applyEditorTheme();
    bool isMenuVisible = true;
    bool isStarted = false;
    bool wireframe =  false;
};