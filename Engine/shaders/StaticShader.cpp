#include "StaticShader.h"

StaticShader::StaticShader()
	: ShaderProgram("Engine/shaders/vertex.glsl", "Engine/shaders/fragment.glsl") {
}

void StaticShader::cleanUp() {
	ShaderProgram::cleanUp();
}

