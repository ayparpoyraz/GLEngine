#include "FreeCamera.h"

FreeCamera::FreeCamera(glm::vec3 position, float speed, float sensitivity)
    : Camera(position), speed(speed), sensitivity(sensitivity),
    yaw(-90.0f), pitch(0.0f) {
    updateFront();
}

void FreeCamera::update(float deltaTime) {}

void FreeCamera::processKeyboard(GLFWwindow* window, float deltaTime) {
    float velocity = speed * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        position += front * velocity;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        position -= front * velocity;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        position -= glm::normalize(glm::cross(front, up)) * velocity;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        position += glm::normalize(glm::cross(front, up)) * velocity;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        position += up * velocity;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        position -= up * velocity;
}

void FreeCamera::processMouse(float xOffset, float yOffset) {
    yaw += xOffset * sensitivity;
    pitch += yOffset * sensitivity;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    updateFront();
}

void FreeCamera::processScroll(float yOffset) {
    speed += yOffset;
    if (speed < 1.0f) speed = 1.0f;
}

void FreeCamera::updateFront() {
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(direction);
}
