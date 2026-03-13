#pragma once
#include "glad/glad.h"
#include <glm/glm.hpp>
#include <string>

class ShaderProgram {
public:
    ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath);
    void StartShader();
    void StopShader();
    void cleanUp();

protected:
    unsigned int programID;
    void loadInt(unsigned int location, int value);
    unsigned int getUniformLocation(const std::string& name);
    void loadMatrix(unsigned int location, glm::mat4 matrix);
private:
    unsigned int vertexShaderID;
    unsigned int fragmentShaderID;

    unsigned int loadShader(const std::string& path, unsigned int type);
};