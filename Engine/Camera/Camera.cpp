#include "Camera.h"

Camera::Camera(glm::vec3 position)
	: position(position), front(glm::vec3(0, 0, -1)), up(glm::vec3(0, 1, 0)) {
}

glm::mat4 Camera::getViewMatrix() {
	return glm::lookAt(position, position + front, up);
}

