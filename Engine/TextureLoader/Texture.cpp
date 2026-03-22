#include "Texture.h"
#include <stb/stb_image.h>
#include <iostream>


Texture::Texture(const std::string& fileName) {
    load("Resource/Textures/"+fileName+".png");
}

void Texture::load(const std::string& path) {
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

    if (data) {
        GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cerr << "Texture yuklenemedi: " << path << std::endl;
    }

    stbi_image_free(data);
}

//void Texture::loadCubemap(const std::vector<std::string>& faces) {
//    glGenTextures(1, &textureID); 
//    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
//
//    int width, height, channels;
//    stbi_set_flip_vertically_on_load(false); 
//
//    for (unsigned int i = 0; i < faces.size(); i++) {
//        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &channels, 0);
//        if (data) {
//            GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;
//            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//            stbi_image_free(data);
//        }
//        else {
//            std::cerr << "Cubemap hatasi: " << faces[i] << std::endl;
//            stbi_image_free(data);
//        }
//    }
//
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
//}
    

void Texture::bind() const {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::cleanUp() {
    glDeleteTextures(1, &textureID);
}