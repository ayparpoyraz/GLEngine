#include "StaticSkyboxShader.h"

StaticSkyboxShader::StaticSkyboxShader()
    : SkyboxShaderProgram("Engine/Skybox/shaders/SkyboxVertex.glsl",
        "Engine/Skybox/shaders/SkyboxFragment.glsl") {
}

void StaticSkyboxShader::cleanUp() {
    SkyboxShaderProgram::cleanUp();
}

void StaticSkyboxShader::connectTextureUnits() {
    loadInt(getUniformLocation("skybox"), 0); 
}

void StaticSkyboxShader::loadTransformationMatrix(glm::mat4 matrix) {
    loadMatrix(getUniformLocation("transformMatrix"), matrix);
}

void StaticSkyboxShader::loadProjectionMatrix(glm::mat4 matrix) {
    loadMatrix(getUniformLocation("projection"), matrix); // ← projection
}

void StaticSkyboxShader::loadViewMatrix(glm::mat4 matrix) {
    loadMatrix(getUniformLocation("view"), matrix); // ← view
}