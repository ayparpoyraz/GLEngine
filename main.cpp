#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Engine/Display/Display.h"
#include "Engine/renderEngine/Loader.h"
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
        -0.5f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f
    };

    float texCoords[] = {
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    Texture texture("Resource/pop_cat.png");

    Loader loader;
    RawModel model = loader.loadToVAO(positions, 12, indices, 6, texCoords, 8, texture);

    // farklı pozisyonlarda 3 entity
    std::vector<Entity> entities = {
        Entity(model, glm::vec3(0.0f,  0.0f, 0.0f), glm::vec3(0), 1.0f),
        Entity(model, glm::vec3(0.6f,  0.0f, 0.0f), glm::vec3(0), 0.5f),
        Entity(model, glm::vec3(-0.6f,  0.0f, 0.0f), glm::vec3(0), 0.5f)
    };

    GameLoop loop;
    loop.run(window, entities);

    loader.cleanUp();
    glfwTerminate();

    return 0;
}