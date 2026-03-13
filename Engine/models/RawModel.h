#pragma once
#include "../TextureLoader/Texture.h"

class RawModel {
public:
    RawModel(unsigned int vaoID, int vertexCount, Texture texture);

    unsigned int getVaoID();
    int getVertexCount();
    Texture& getTexture();

private:
    unsigned int vaoID;
    int vertexCount;
    Texture texture;
};