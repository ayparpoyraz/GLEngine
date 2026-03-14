#include "VBO.h"

VBO::VBO() {
    glGenBuffers(1, &vboID);
}

void VBO::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
}

void VBO::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::storeData(float* data, int count, int attrib, int size) {
    bind();
    glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), data, GL_STATIC_DRAW);
    glVertexAttribPointer(attrib, size, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(attrib);
    unbind();
}

void VBO::cleanUp() {
    glDeleteBuffers(1, &vboID);
}