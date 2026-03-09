#pragma once
#include "glad/glad.h"
#include <string>

class ShaderProgram {
public:
	ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath);
	void StartShader();
	void StopShader();
	void cleanUp();
private:
	unsigned int programID;
	unsigned int vertexShaderID;
	unsigned int fragmentShaderID;

	unsigned int loadShader(const std::string& path, unsigned int type);
};
