#include "GameLoop.h"

void GameLoop::run(GLFWwindow* window, RawModel& model) {
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        renderer.prepare();
        renderer.render(model);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void GameLoop::processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}