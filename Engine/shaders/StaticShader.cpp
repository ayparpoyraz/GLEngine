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