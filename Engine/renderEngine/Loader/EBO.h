#pragma once
#include <glad/glad.h>

class EBO {
public:
    EBO();
    void bind();
    void unbind();
    void cleanUp();
    void storeData(unsigned int* indices, int count);

private:
    unsigned int eboID;
};