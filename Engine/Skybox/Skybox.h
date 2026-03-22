#pragma once
#include "shaders/StaticSkyboxShader.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>

class Skybox {
public:
    void init();
    unsigned int loadCubemap(std::vector<std::string> faces);
    void render(glm::mat4 view, glm::mat4 projection);
    void cleanUp();

private:
    unsigned int VAO = 0;
    unsigned int VBO = 0;
    unsigned int EBO = 0;
    unsigned int textureID = 0;
    unsigned int cubemapTexture = 0;
    StaticSkyboxShader shader;

};