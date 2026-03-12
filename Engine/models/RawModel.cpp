#include "RawModel.h"

RawModel::RawModel(unsigned int vaoID, int vertexCount, Texture texture)
    : vaoID(vaoID), vertexCount(vertexCount), texture(texture) {
}

unsigned int RawModel::getVaoID() { return vaoID; }
int RawModel::getVertexCount() { return vertexCount; }
Texture& RawModel::getTexture() { return texture; }