#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Engine/renderEngine/Display.h"
#include "Engine/renderEngine/Loader.h"
#include "Engine/models/RawModel.h"
#include "Engine/Core/GameLoop.h"

int main() {
	GLFWwindow* window = createWindow(1200, 800, "Game");
	if (!window) return -1;

	float vertices[] = {
		-0.5f,  0.5f, 0.0f,  // V0 sol üst
		-0.5f, -0.5f, 0.0f,  // V1 sol alt
		 0.5f, -0.5f, 0.0f,  // V2 sað alt
		 0.5f,  0.5f, 0.0f   // V3 sað üst
	};

	unsigned int indices[] = {
		0, 1, 2,  // 1. üçgen
		2, 3, 0   // 2. üçgen
	};


	Loader loader;
	RawModel model = loader.loadToVAO(vertices, 12, indices, 6);

	GameLoop loop;
	loop.run(window, model);

	loader.cleanUp();
	glfwTerminate();

	return 0;
}