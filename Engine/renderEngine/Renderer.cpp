#include "Renderer.h"

void Renderer::prepare() {
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Change Background
}

void Renderer::render(RawModel& model) {
	glBindVertexArray(model.getVaoID());
	model.getTexture().bind();
	glDrawElements(GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, 0);
	model.getTexture().unbind();
	glBindVertexArray(0);
}