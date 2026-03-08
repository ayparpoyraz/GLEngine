#include "RawModel.h"

RawModel::RawModel(unsigned int vaoID, int vertexCount)
    : vaoID(vaoID), vertexCount(vertexCount) {
}

unsigned int RawModel::getVaoID() { return vaoID; }
int RawModel::getVertexCount() { return vertexCount; }