#include "VAO.h"

VAO::VAO() {
	glGenVertexArrays(1, &vaoID);
}

void VAO::bind() {
	glBindVertexArray(vaoID);
}

void VAO::unbind() {
	glBindVertexArray(0);
}

void VAO::cleanUp() {
	glDeleteBuffers(1, &vaoID);
}