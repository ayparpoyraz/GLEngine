#pragma once

#include <vector>
#include "glad/glad.h"
#include "../models/RawModel.h"
#include "../TextureLoader/Texture.h"


class Loader {
public:
    RawModel loadToVAO(float* positions, int posCount, unsigned int* indices,
        int indexCount, float* textureCoords, int texCount, Texture texture);
    void cleanUp();
    
private:
    std::vector<unsigned int> vaos;
    std::vector<unsigned int> vbos;
    std::vector<unsigned int> ebos;

    unsigned int createVAO();
    void storeDataAttributeList(int attribNumber, float* data, int count, int size);
    void bindIndicesBuffer(unsigned int* indices, int count);
    void unbindVAO();
};