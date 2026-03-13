#include "GameLoop.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

void GameLoop::run(GLFWwindow* window, std::vector<Entity>& entities) {

    // projection loop dışında
    glm::mat4 projection = glm::perspective(
        glm::radians(70.0f),
        1200.0f / 800.0f,
        0.1f,
        1000.0f
    );

    shader.StartShader();
    shader.loadProjectionMatrix(projection);  // ← shader'a gönder
    shader.connectTextureUnits();
    shader.StopShader();

    float rotation = 0.0f;

    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        rotation += 0.5f;

        renderer.prepare();
        shader.StartShader();

        for (Entity& entity : entities) {
            entity.setRotation(glm::vec3(rotation, rotation, 0.0f));
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