#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Engine/Display/Display.h"
#include "Engine/Renderer/Loader/Loader.h"
#include "Engine/models/RawModel.h"
#include "Engine/TextureLoader/Texture.h"
#include "Engine/math/Math.h"
#include "Engine/entities/Entity.h"
#include "Engine/OBJLoader/OBJLoader.h"
#include <vector>

#define EDITOR_MODE

#ifdef EDITOR_MODE
#include "Engine/Core/Editor/Editor.h"
#include "Engine/Core/GameLoop.h"  
#else
#include "Engine/Core/GameLoop.h"
#endif

int main() {

#ifdef EDITOR_MODE
    GLFWwindow* window = createWindow(1920, 1080, "HolyEngine");
#else
    GLFWwindow* window = createFullScreen(1920, 1080, "Game");
#endif

    if (!window) return -1;

    Loader loader;
    Texture texture("texture");
    RawModel model = OBJLoader::loadOBJ("dragon", loader, texture);

    std::vector<Entity> entities = {
        Entity(model, glm::vec3(2.0f, 0.0f, -3.0f), glm::vec3(0.0f), 1.0f)
    };

#ifdef EDITOR_MODE
    Editor editor;
    bool startGame = editor.run(window, entities/*, model*/);
    glfwDestroyWindow(window);

    if (startGame) {
        GLFWwindow* gameWindow = createFullScreen(1920, 1080, "Game");
        if (gameWindow) {
            GameLoop game;
            game.run(gameWindow, entities);
            glfwDestroyWindow(gameWindow);
        }
    }
#else
    GameLoop game;
    game.run(window, entities);
#endif

    glfwTerminate();
    return 0;
}