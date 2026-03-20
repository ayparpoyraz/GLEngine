#pragma once
#include "../Camera.h"
#include <GLFW/glfw3.h>

class masterCamera : public Camera {
public:
    masterCamera(glm::vec3 position = glm::vec3(0, 0, 5),
        float speed = 50.0f,
        float sensitivity = 0.1f,
        glm::vec3 target = glm::vec3(0),
        float radius = 5.0f);

    void update(float deltaTime) override;
    void updateInput(GLFWwindow* window, float deltaTime,
        float xOffset, float yOffset, float scrollOffset);

    void setTarget(glm::vec3 target) { this->target = target; }

private:
    float speed;
    float sensitivity;
    float yaw = -90.0f;
    float pitch = 0.0f;

    glm::vec3 target;
    float radius;

    float orbitRadius = 5.0f;
    float orbitYaw = 0.0f;
    float orbitPitch = 0.0f;
    bool orbitInitialized = false;

    void processFreeCam(GLFWwindow* window, float deltaTime, float xOffset, float yOffset);
    void processOrbit(float xOffset, float yOffset);
    void processScrollInput(float scrollOffset);
    void updateFront();
};