#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    Camera(glm::vec3 position);

    virtual void update(float deltaTime) = 0;
    glm::mat4 getViewMatrix();

    glm::vec3 getPosition() { return position; }
    void setPosition(glm::vec3 pos) { position = pos; }

protected:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
};