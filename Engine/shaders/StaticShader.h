#pragma once
#include <glm/glm.hpp>
#include "ShaderProgram.h"

class StaticShader : public ShaderProgram {
public:
    StaticShader();
    void cleanUp();
    void connectTextureUnits();
    void loadTransformationMatrix(glm::mat4 matrix);
    void loadProjectionMatrix(glm::mat4 matrix);
    void loadViewMatrix(glm::mat4 matrix);
};