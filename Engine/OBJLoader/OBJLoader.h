#pragma once
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "../models/RawModel.h"
#include "../Renderer/Loader/Loader.h"
#include "../TextureLoader/Texture.h"

class OBJLoader {
public:
    static RawModel loadOBJ(const std::string& path, Loader& loader, Texture texture);

};  