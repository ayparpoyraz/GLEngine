#pragma once

#include <vector>
#include "glad/glad.h"
#include "../models/RawModel.h"


class Loader {
public:
    RawModel loadToVAO(float* positions, int count);
    void cleanUp();
    
private:
    std::vector<unsigned int> vaos;
    std::vector<unsigned int> vbos;

    unsigned int createVAO();
    void storeDataAttributeList(int attribNumber, float* data, int count);
    void unbindVAO();
};