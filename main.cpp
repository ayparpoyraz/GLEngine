#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Engine/renderEngine/Display.h"
#include "Engine/renderEngine/Loader.h"
#include "Engine/models/RawModel.h"
#include "Engine/Core/GameLoop.h"
#include "Engine/TextureLoader/Texture.h"

int main() {
    GLFWwindow* window = createWindow(1200, 800, "Game");
    if (!window) return -1;

    float positions[] = {
        -0.5f,  0.5f, 0.0f,  // V0 sol üst
        -0.5f, -0.5f, 0.0f,  // V1 sol alt
         0.5f, -0.5f, 0.0f,  // V2 sað alt
         0.5f,  0.5f, 0.0f   // V3 sað üst
    };

    float texCoords[] = {
        0.0f, 1.0f,  // V0
        0.0f, 0.0f,  // V1
        1.0f, 0.0f,  // V2
        1.0f, 1.0f   // V3
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    Texture texture("Resource/pop_cat.png");

    Loader loader;
    RawModel model = loader.loadToVAO(positions, 12, indices, 6, texCoords, 8, texture);

    GameLoop loop;
    loop.run(window, model);

    loader.cleanUp();
    glfwTerminate();

    return 0;
}