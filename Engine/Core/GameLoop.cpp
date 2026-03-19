#include "GameLoop.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

void GameLoop::run(GLFWwindow* window, std::vector<Entity>& entities) {

    int screenWidth, screenHeight;
    glfwGetWindowSize(window, &screenWidth, &screenHeight);

    glm::mat4 projection = glm::perspective(
        glm::radians(70.0f),
        (float)screenWidth / (float)screenHeight,
        0.1f,
        1000.0f
    );

    shader.StartShader();
    shader.loadProjectionMatrix(projection);
    shader.connectTextureUnits();
    shader.StopShader();

    float lastFrame = 0.0f;
    int selectedEntity = 0;

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);
        camera.processKeyboard(window, deltaTime);

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            camera.processMouse(getMouseXOffset(), getMouseYOffset());
        }
        else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }

        if (!entities.empty() && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) {
            glm::vec3 rot = entities[selectedEntity].getRotation(); 
            rot.y += getMouseXOffset() * 0.5f;
            rot.x += getMouseYOffset() * 0.5f;
            entities[selectedEntity].setRotation(rot);
        }

        resetScrollOffset();
        resetMouseOffset();

        renderer.prepare();
        shader.StartShader();
        shader.loadViewMatrix(camera.getViewMatrix());

        for (Entity& entity : entities) {
            glm::mat4 matrix = Math::createTransformationMatrix(
                entity.getPosition(),
                entity.getRotation(),
                entity.getScale()
            );
            shader.loadTransformationMatrix(matrix);
            renderer.render(entity.getModel());
        }

        shader.StopShader();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    shader.cleanUp();
}

void GameLoop::processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}