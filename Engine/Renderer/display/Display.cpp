#include "Display.h"


void framebuffer_size_callback(GLFWwindow* window, int WIDTH, int HEIGHT) {
	glViewport(0, 0, WIDTH, HEIGHT);
}



GLFWwindow* createWindow(int WIDTH, int HEIGHT, const char* title) {

	if (!glfwInit())[
		std::cerr << "GLFW cannot be start";
		return nullptr;
	]

}