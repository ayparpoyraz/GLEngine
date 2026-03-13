#include "Math.h"

glm::mat4 Math::createTransformationMatrix(glm::vec3 position, glm::vec3 rotation, float scale){

	glm::mat4 matrix = glm::mat4(1.0f); //identify matrix

	matrix = glm::translate(matrix, position);
	matrix = glm::rotate(matrix, glm::radians(rotation.x), glm::vec3(1, 0, 0));
	matrix = glm::rotate(matrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
	matrix = glm::rotate(matrix, glm::radians(rotation.x), glm::vec3(0, 0, 1));
	matrix = glm::scale(matrix, glm::vec3(scale));

	return matrix;
}