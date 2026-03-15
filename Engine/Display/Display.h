#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

GLFWwindow* createWindow(int WIDTH, int HEIGHT, const char* TITLE);
GLFWwindow* createFullScreen(int WIDTH, int HEIGHT, const char* TITLE);
void framebuffer_size_callback(GLFWwindow* window, int WIDTH, int HEIGHT);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);


float getScrollOffset();
float getMouseXOffset();
float getMouseYOffset();

void resetMouseOffset();
void resetScrollOffset();