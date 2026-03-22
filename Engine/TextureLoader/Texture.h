#pragma once
#include <glad/glad.h>
#include <vector>
#include <string>


class Texture {
public:
	Texture(const std::string& fileName);
	/*void loadCubemap(const std::vector<std::string>& faces);*/
	void bind() const;
	void unbind() const;
	void cleanUp();


	unsigned int getID() const { return textureID; }

private:
	unsigned int textureID;
	void load(const std::string& path);
	
};