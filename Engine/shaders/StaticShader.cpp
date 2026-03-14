#include "StaticShader.h"

StaticShader::StaticShader()
	: ShaderProgram("Engine/shaders/vertex.glsl", "Engine/shaders/fragment.glsl") {
}

void StaticShader::cleanUp() {
	ShaderProgram::cleanUp();
}

void StaticShader::connectTextureUnits() {
	loadInt(getUniformLocation("textureSampler"), 0); // texture unit 0
}
void StaticShader::loadTransformationMatrix(glm::mat4 matrix) {
	loadMatrix(getUniformLocation("transformMatrix"), matrix);
}

void StaticShader::loadProjectionMatrix(glm::mat4 matrix) {
	loadMatrix(getUniformLocation("projectionMatrix"), matrix);
}
void StaticShader::loadViewMatrix(glm::mat4 matrix) {
	loadMatrix(getUniformLocation("viewMatrix"), matrix);
}