#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Engine/Display/Display.h"
#include "Engine/renderEngine/Loader/Loader.h"
#include "Engine/models/RawModel.h"
#include "Engine/Core/GameLoop.h"
#include "Engine/TextureLoader/Texture.h"
#include "Engine/math/Math.h"
#include "Engine/entities/Entity.h"
#include <vector>

int main() {
    GLFWwindow* window = createWindow(1200, 800, "Game");
    if (!window) return -1;

    float positions[] = {
        // ön yüz
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         // arka yüz
         -0.5f,  0.5f, -0.5f,
         -0.5f, -0.5f, -0.5f,
          0.5f, -0.5f, -0.5f,
          0.5f,  0.5f, -0.5f
    };

    float texCoords[] = {
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f
    };

    unsigned int indices[] = {
        // ön
        0, 1, 2,  2, 3, 0,
        // arka
        4, 5, 6,  6, 7, 4,
        // sol
        4, 5, 1,  1, 0, 4,
        // sağ
        3, 2, 6,  6, 7, 3,
        // üst
        4, 0, 3,  3, 7, 4,
        // alt
        1, 5, 6,  6, 2, 1
    };

    Texture texture("Resource/pop_cat.png");

    Loader loader;
    RawModel model = loader.loadToVAO(positions, 24, indices, 36, texCoords, 16, texture);

    std::vector<Entity> entities = {
        Entity(model, glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.0f), 1.0f),
        Entity(model, glm::vec3(2.0f, 0.0f, -3.0f), glm::vec3(0.0f), 1.0f),
        Entity(model, glm::vec3(-2.0f, 0.0f, -3.0f), glm::vec3(0.0f), 0.5f)
    };

    GameLoop loop;
    loop.run(window, entities);

    glfwTerminate();

    return 0;
}