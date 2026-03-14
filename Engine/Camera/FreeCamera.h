#pragma once
#include "Camera.h"
#include <GLFW/glfw3.h>

class FreeCamera : public Camera {
public:
    FreeCamera(glm::vec3 position, float speed = 5.0f, float sensitivity = 0.1f);

    void update(float deltaTime) override;
    void processKeyboard(GLFWwindow* window, float deltaTime);
    void processMouse(float xOffset, float yOffset);
    void processScroll(float yOffset);

private:
    float speed;
    float sensitivity;
    float yaw;
    float pitch;

    void updateFront();
};