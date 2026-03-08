#include "Display.h"

void framebuffer_size_callback(GLFWwindow* window, int WIDTH, int HEIGHT) {
	glViewport(0, 0, WIDTH, HEIGHT);
}

GLFWwindow* createWindow(int WIDTH, int HEIGHT, const char* TITLE) {

	if (!glfwInit()) {
		std::cerr << "GLFW cannot be started\n";
		return nullptr;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, nullptr, nullptr);
	if(!window)
	{
		std::cerr << "Display cannot be Started\n";
		glfwTerminate();
		return nullptr;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "GLAD cannot be Started!\n";
		return nullptr;
	}

	// Initial viewport and vsync
	glViewport(0, 0, WIDTH, HEIGHT);
	glfwSwapInterval(1);

	return window;
}