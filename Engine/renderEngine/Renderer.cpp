#include "Renderer.h"

void Renderer::prepare() {
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Change Background
}

void Renderer::render(RawModel& model) {
	glBindVertexArray(model.getVaoID());
	glDrawElements(GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}