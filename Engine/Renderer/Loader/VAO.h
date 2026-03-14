#pragma once
#include <glad/glad.h>

class VAO {
public:
	VAO();
	void bind();
	void unbind();
	void cleanUp();
	unsigned int getID() { return vaoID; }
private:
	unsigned int vaoID;
};