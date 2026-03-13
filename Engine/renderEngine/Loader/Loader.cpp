#include "Loader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

RawModel Loader::loadToVAO(float* positions, int posCount,
    unsigned int* indices, int indexCount,
    float* texCoords, int texCount,
    Texture texture) {
    VAO vao;
    vao.bind();

    EBO ebo;
    ebo.storeData(indices, indexCount);

    VBO vbo0;
    vbo0.storeData(positions, posCount, 0, 3);

    VBO vbo1;
    vbo1.storeData(texCoords, texCount, 1, 2);

    vao.unbind();
    return RawModel(vao.getID(), indexCount, texture);
}

void Loader::cleanUp() {
    //pass
}