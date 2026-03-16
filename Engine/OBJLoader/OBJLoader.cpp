#include "OBJLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

RawModel OBJLoader::loadOBJ(const std::string& fileName, Loader& loader, Texture texture) {
    std::ifstream file("Resource/OBJs/" + fileName + ".obj");
    if (!file.is_open()) {
        std::cerr << "The OBJ file cannot be opened: " << fileName << std::endl;
        return RawModel(0,0,texture);
    }

    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> texCoords;
    std::vector<glm::vec3> normals;

    std::vector<float> finalPositions;
    std::vector<float> finalTexCoords;
    std::vector<unsigned int> indices;

    std::map<std::string, unsigned int> vertexCache;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string prefix;
        ss >> prefix;

        if (prefix == "v") {
            glm::vec3 pos;
            ss >> pos.x >> pos.y >> pos.z;
            positions.push_back(pos);
        }
        else if (prefix == "vt") {
            glm::vec2 tex;
            ss >> tex.x >> tex.y;
            texCoords.push_back(tex);
        }
        else if (prefix == "vn") {
            glm::vec3 norm;
            ss >> norm.x >> norm.y >> norm.z;
            normals.push_back(norm);
        }
        else if (prefix == "f") {
            std::vector<std::string> verts;
            std::string v;
            while (ss >> v) verts.push_back(v);

            for (int i = 1; i < (int)verts.size() - 1; i++) {
                auto processVertex = [&](const std::string& vertStr) {
                    if (vertexCache.count(vertStr)) {
                        indices.push_back(vertexCache[vertStr]);
                        return;
                    }

                    std::istringstream vs(vertStr);
                    std::string idx;
                    std::vector<int> parts;
                    while (std::getline(vs, idx, '/'))
                        parts.push_back(idx.empty() ? 0 : std::stoi(idx));

                    int posIdx = parts[0] - 1;
                    int texIdx = (parts.size() > 1 && parts[1] > 0) ? parts[1] - 1 : -1;

                    unsigned int newIndex = (unsigned int)(finalPositions.size() / 3);
                    vertexCache[vertStr] = newIndex;
                    indices.push_back(newIndex);

                    if (posIdx >= 0 && posIdx < (int)positions.size()) {
                        finalPositions.push_back(positions[posIdx].x);
                        finalPositions.push_back(positions[posIdx].y);
                        finalPositions.push_back(positions[posIdx].z);
                    }
                    else {
                        finalPositions.push_back(0.0f);
                        finalPositions.push_back(0.0f);
                        finalPositions.push_back(0.0f);
                    }

                    if (texIdx >= 0 && texIdx < (int)texCoords.size()) {
                        finalTexCoords.push_back(texCoords[texIdx].x);
                        finalTexCoords.push_back(1.0f - texCoords[texIdx].y);
                    }
                    else {
                        finalTexCoords.push_back(0.0f);
                        finalTexCoords.push_back(0.0f);
                    }
                    };

                processVertex(verts[0]);
                processVertex(verts[i]);
                processVertex(verts[i + 1]);
            }
        }
    }

    return loader.loadToVAO(
        finalPositions.data(), (int)finalPositions.size(),
        indices.data(), (int)indices.size(),
        finalTexCoords.data(), (int)finalTexCoords.size(),
        texture
    );
}