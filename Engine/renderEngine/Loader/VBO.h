#pragma once
#include <glad/glad.h>

class VBO {
public:
    VBO();
    void bind();
    void unbind();
    void cleanUp();
    void storeData(float* data, int count, int attrib, int size);

private:
    unsigned int vboID;
};