#include "Renderer.h"

void Renderer::prepare() {
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Change Background
}

void Renderer::render(RawModel& model) {
	glBindVertexArray(model.getVaoID());
	glDrawArrays(GL_TRIANGLES, 0, model.getVertexCount());
	glBindVertexArray(0);
}