#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Engine/renderEngine/Display.h"
#include "Engine/renderEngine/Loader.h"
#include "Engine/models/RawModel.h"
#include "Engine/Core/GameLoop.h"

int main() {
	GLFWwindow* window = createWindow(800, 600, "Game");
	if (!window) return -1;

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
   0.5f, -0.5f, 0.0f,
   0.0f,  0.5f, 0.0f
	};

	Loader loader;
	RawModel model = loader.loadToVAO(vertices, 9);

	GameLoop loop;
	loop.run(window, model);

	loader.cleanUp();
	glfwTerminate();

	return 0;
}