#include "OrbitCamera.h"

OrbitCamera::OrbitCamera(glm::vec3 target, float radius)
    : Camera(glm::vec3(0, 0, radius)), target(target), radius(radius) {
    updatePosition();
}

void OrbitCamera::processMouse(float xOffset, float yOffset) {
    yaw += xOffset * 0.3f;
    pitch += yOffset * 0.3f;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    updatePosition();
}

void OrbitCamera::processScroll(float yOffset) {
    radius -= yOffset * 0.5f;
    if (radius < 1.0f) radius = 1.0f;
    updatePosition();
}

void OrbitCamera::updatePosition() {
    position.x = target.x + radius * cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    position.y = target.y + radius * sin(glm::radians(pitch));
    position.z = target.z + radius * cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    front = glm::normalize(target - position);
}