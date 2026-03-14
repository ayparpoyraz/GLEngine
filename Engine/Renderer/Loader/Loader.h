#pragma once
#include <glad/glad.h>
#include "../../models/RawModel.h"
#include "../../TextureLoader/Texture.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

class Loader {
public:
    RawModel loadToVAO(float* positions, int posCount,
        unsigned int* indices, int indexCount,
        float* texCoords, int texCount,
        Texture texture);
};