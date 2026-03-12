#pragma once
#include <glad/glad.h>
#include <string>


class Texture {
public:
	Texture(const std::string& path);
	void bind() const;
	void unbind() const;
	void cleanUp();

	unsigned int getID() const { return textureID; }

private:
	unsigned int textureID;
	void load(const std::string& path);

};