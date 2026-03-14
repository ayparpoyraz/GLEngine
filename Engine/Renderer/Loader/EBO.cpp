#include "EBO.h"

EBO::EBO() {
    glGenBuffers(1, &eboID);
}

void EBO::bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
}

void EBO::unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::storeData(unsigned int* indices, int count) {
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
}

void EBO::cleanUp() {
    glDeleteBuffers(1, &eboID);
}