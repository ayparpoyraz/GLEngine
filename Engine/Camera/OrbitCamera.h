#pragma once
#include "Camera.h"
#include <GLFW/glfw3.h>

class OrbitCamera : public Camera {
public:
    OrbitCamera(glm::vec3 target, float radius = 5.0f);

    void update(float deltaTime) override {}
    void processMouse(float xOffset, float yOffset);
    void processScroll(float yOffset);
    void setTarget(glm::vec3 target) { this->target = target; }

private:
    glm::vec3 target;
    float radius;
    float yaw = 0.0f;
    float pitch = 0.0f;

    void updatePosition();
};