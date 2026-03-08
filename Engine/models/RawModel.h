#pragma once


class RawModel {
public:
    RawModel(unsigned int vaoID, int vertexCount);

    unsigned int getVaoID();
    int getVertexCount();

private:
    unsigned int vaoID;
    int vertexCount;
};