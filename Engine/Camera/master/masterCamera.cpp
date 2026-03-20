#include "masterCamera.h"

masterCamera::masterCamera(glm::vec3 position, float speed,
    float sensitivity, glm::vec3 target, float radius)
    : Camera(position), speed(speed), sensitivity(sensitivity),
    yaw(-90.0f), pitch(0.0f), target(target), radius(radius) {
    updateFront();
}

void masterCamera::update(float deltaTime) {}


//MasterCamera:updateInput
void masterCamera::updateInput(GLFWwindow* window, float deltaTime,
    float xOffset, float yOffset, float scrollOffset) {

    bool rightClick = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;
    bool middleClick = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS;

     
    float velocity = speed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        velocity *= 1.5f;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) position += front * velocity;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) position -= front * velocity;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        position -= glm::normalize(glm::cross(front, up)) * velocity;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        position += glm::normalize(glm::cross(front, up)) * velocity;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) position += up * velocity;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) position -= up * velocity;

    // mouse sadece tıklandığında
    if (rightClick) {
        orbitInitialized = false;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        yaw += xOffset * sensitivity;
        pitch += yOffset * sensitivity;
        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;
        updateFront();
    }
    else if (middleClick) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        processOrbit(xOffset, yOffset);
    }
    else {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        orbitInitialized = false;
    }

    if (scrollOffset != 0.0f)
        processScrollInput(scrollOffset);
}

void masterCamera::processFreeCam(GLFWwindow* window, float deltaTime,
    float xOffset, float yOffset) {



    float velocity = speed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        velocity *= 5.0f;

    //if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) position += front * velocity;
    //if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) position -= front * velocity;
    //if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    //    position -= glm::normalize(glm::cross(front, up)) * velocity;
    //if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    //    position += glm::normalize(glm::cross(front, up)) * velocity;
    //if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) position += up * velocity;
    //if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) position -= up * velocity;

    yaw += xOffset * sensitivity;
    pitch += yOffset * sensitivity;
    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;
    updateFront();
}

void masterCamera::processOrbit(float xOffset, float yOffset) {
    if (!orbitInitialized) {
        glm::vec3 dir = position - target;
        orbitRadius = glm::length(dir);
        orbitYaw = glm::degrees(atan2(dir.z, dir.x));
        orbitPitch = glm::degrees(asin(dir.y / orbitRadius));
        orbitInitialized = true;
    }

    orbitYaw += xOffset * 0.3f;
    orbitPitch += yOffset * 0.3f;
    if (orbitPitch > 89.0f) orbitPitch = 89.0f;
    if (orbitPitch < -89.0f) orbitPitch = -89.0f;

    position.x = target.x + orbitRadius * cos(glm::radians(orbitPitch)) * cos(glm::radians(orbitYaw));
    position.y = target.y + orbitRadius * sin(glm::radians(orbitPitch));
    position.z = target.z + orbitRadius * cos(glm::radians(orbitPitch)) * sin(glm::radians(orbitYaw));
    front = glm::normalize(target - position);
}

void masterCamera::processScrollInput(float scrollOffset) {
    orbitRadius -= scrollOffset * 0.5f;
    if (orbitRadius < 1.0f) orbitRadius = 1.0f;

    position.x = target.x + orbitRadius * cos(glm::radians(orbitPitch)) * cos(glm::radians(orbitYaw));
    position.y = target.y + orbitRadius * sin(glm::radians(orbitPitch));
    position.z = target.z + orbitRadius * cos(glm::radians(orbitPitch)) * sin(glm::radians(orbitYaw));
}

void masterCamera::updateFront() {
    glm::vec3 dir;
    dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    dir.y = sin(glm::radians(pitch));
    dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(dir);
}