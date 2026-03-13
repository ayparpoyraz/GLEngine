#pragma once
#include "ShaderProgram.h"

class StaticShader : public ShaderProgram {
public:
	StaticShader();
	void cleanUp();
	void connectTextureUnits();
	void loadTransformationMatrix(glm::mat4 matrix);
};
