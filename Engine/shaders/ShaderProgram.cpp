#include "ShaderProgram.h"
#include <fstream>
#include <sstream>
#include <iostream>

ShaderProgram::ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath) {
	vertexShaderID = loadShader(vertexPath, GL_VERTEX_SHADER);
	fragmentShaderID = loadShader(fragmentPath, GL_FRAGMENT_SHADER);

	//ikisini birbirine baðlýyoruz
	programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);
}
void ShaderProgram::StartShader() {
	//programID'sini kullan
	glUseProgram(programID);
}
void ShaderProgram::StopShader() {
	glUseProgram(0);
}
void ShaderProgram::cleanUp() {
	StopShader();
	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
	glDeleteProgram(programID);
}

unsigned int ShaderProgram::loadShader(const std::string& path, unsigned int type) {

	//Dosya Oku
	std::ifstream shaderFile(path);
	std::stringstream shaderStream;
	shaderStream << shaderFile.rdbuf();
	std::string shaderCode = shaderStream.str();
	const char* code = shaderCode.c_str();

	//Derle 
	unsigned int shaderID = glCreateShader(type);
	glShaderSource(shaderID, 1, &code, nullptr);
	glCompileShader(shaderID);

	// hata kontrolü 
	int success;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
		std::cerr << "Shader compilation failed: " << infoLog << std::endl;
	}

	return shaderID;
}
