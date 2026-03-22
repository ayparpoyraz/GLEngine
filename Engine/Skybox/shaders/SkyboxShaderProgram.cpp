#include "SkyBoxShaderProgram.h"
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>
#include <iostream>

SkyboxShaderProgram::SkyboxShaderProgram(const std::string& vertexPath, const std::string& fragmentPath) {
	vertexShaderID = loadShader(vertexPath, GL_VERTEX_SHADER);
	fragmentShaderID = loadShader(fragmentPath, GL_FRAGMENT_SHADER);

	programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);
}
void SkyboxShaderProgram::StartShader() {
	glUseProgram(programID);
}
void SkyboxShaderProgram::StopShader() {
	glUseProgram(0);
}
void SkyboxShaderProgram::cleanUp() {
	StopShader();
	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
	glDeleteProgram(programID);
}

void SkyboxShaderProgram::loadInt(unsigned int location, int value) {
	glUniform1i(location, value);
}

unsigned int SkyboxShaderProgram::getUniformLocation(const std::string& name) {
	return glGetUniformLocation(programID, name.c_str());
}

void SkyboxShaderProgram::loadMatrix(unsigned int location, glm::mat4 matrix) {
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}


unsigned int SkyboxShaderProgram::loadShader(const std::string& path, unsigned int type) {


	std::ifstream shaderFile(path);
	std::stringstream shaderStream;
	shaderStream << shaderFile.rdbuf();
	std::string shaderCode = shaderStream.str();
	const char* code = shaderCode.c_str();

	unsigned int shaderID = glCreateShader(type);
	glShaderSource(shaderID, 1, &code, nullptr);
	glCompileShader(shaderID);
	int success;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
		std::cerr << "Shader compilation failed: " << infoLog << std::endl;
	}

	return shaderID;
}
