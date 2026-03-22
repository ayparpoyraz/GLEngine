#pragma once
#include <glm/glm.hpp>
#include <string>
#include "SkyboxShaderProgram.h"

class StaticSkyboxShader : public SkyboxShaderProgram {
public:
    StaticSkyboxShader();
    void cleanUp();
    void connectTextureUnits();
    void loadTransformationMatrix(glm::mat4 matrix);
    void loadProjectionMatrix(glm::mat4 matrix);
    void loadViewMatrix(glm::mat4 matrix);
};