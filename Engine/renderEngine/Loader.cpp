#include "Loader.h"

RawModel Loader::loadToVAO(float* position, int count) {
	unsigned int vaoID = createVAO();
	storeDataAttributeList(0, position, count);
	unbindVAO();
	return RawModel(vaoID, count / 3);
}

void Loader::cleanUp() {
	for (unsigned int vao : vaos) {
		glDeleteVertexArrays(1, &vao);
	}
	for (unsigned int vbo : vbos) {
		glDeleteBuffers(1, &vbo);
	}
}

unsigned int Loader::createVAO() {
	unsigned int vaoID;
	glGenVertexArrays(1, &vaoID);
	vaos.push_back(vaoID);
	glBindVertexArray(vaoID);
	return vaoID;
}

void Loader::storeDataAttributeList(int attribNumber, float* data, int count) {
	unsigned int vboID;
	glGenBuffers(1, &vboID);
	vbos.push_back(vboID);

	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), data, GL_STATIC_DRAW);

	glVertexAttribPointer(attribNumber, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(attribNumber);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::unbindVAO() {
	glBindVertexArray(0);
}