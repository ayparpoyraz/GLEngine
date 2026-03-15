#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Engine/Display/Display.h"
#include "Engine/Renderer/Loader/Loader.h"
#include "Engine/models/RawModel.h"
#include "Engine/TextureLoader/Texture.h"
#include "Engine/math/Math.h"
#include "Engine/entities/Entity.h"
#include <vector>
//
//#define EDITOR_MODE

#ifdef EDITOR_MODE
#include "Engine/Core/Editor/Editor.h"
GLFWwindow* window = createWindow(1920, 1080, "GameEngine");
#else
#include "Engine/Core/GameLoop.h"
GLFWwindow* window = createFullScreen(1920, 1080, "GameEngine");
#endif

int main() {
   
    if (!window) return -1;

    float positions[] = {
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f
    };

    float texCoords[] = {
        0.0f, 1.0f,  0.0f, 0.0f,  1.0f, 0.0f,  1.0f, 1.0f,
        0.0f, 1.0f,  0.0f, 0.0f,  1.0f, 0.0f,  1.0f, 1.0f,
        0.0f, 1.0f,  0.0f, 0.0f,  1.0f, 0.0f,  1.0f, 1.0f,
        0.0f, 1.0f,  0.0f, 0.0f,  1.0f, 0.0f,  1.0f, 1.0f,
        0.0f, 1.0f,  0.0f, 0.0f,  1.0f, 0.0f,  1.0f, 1.0f,
        0.0f, 1.0f,  0.0f, 0.0f,  1.0f, 0.0f,  1.0f, 1.0f
    };

    unsigned int indices[] = {
        0,  1,  2,   2,  3,  0,
        4,  5,  6,   6,  7,  4,
        8,  9,  10,  10, 11, 8,
        12, 13, 14,  14, 15, 12,
        16, 17, 18,  18, 19, 16,
        20, 21, 22,  22, 23, 20
    };

    Texture texture("Resource/Textures/texture.png");

    Loader loader;
    RawModel model = loader.loadToVAO(positions, 72, indices, 36, texCoords, 48, texture);

    std::vector<Entity> entities = {
        Entity(model, glm::vec3(2.0f, 0.0f, -3.0f), glm::vec3(0.0f), 1.0f)
    };

#ifdef EDITOR_MODE
    Editor loop;
    loop.run(window, entities, model);
#else
    GameLoop loop;
    loop.run(window, entities);
#endif

    glfwTerminate();
    return 0;
}