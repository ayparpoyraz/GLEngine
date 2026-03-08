#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

GLFWwindow* createWindow(int WIDTH, int HEIGHT, const char* title);
void framebuffer_size_callback(GLFWwindow* window, int WIDTH, int HEIGHT);