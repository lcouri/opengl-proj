#include "Texture.h"

#include <iostream>

#include "stb_image.h"

Texture::Texture() {
	currentTexId = 0;
}

void Texture::addTextureUnit(const std::string &imagePath, const GLenum colorMode) {
	addTextureUnit(imagePath, colorMode, GL_REPEAT);
}

void Texture::addTextureUnit(const std::string &imagePath, const GLenum colorMode, const GLenum wrappingMode) {
	addTextureUnit(imagePath, colorMode, wrappingMode, GL_LINEAR);
}

void Texture::addTextureUnit(const std::string &imagePath, const GLenum colorMode, const GLenum wrappingMode, const GLenum filter) {
	glGenTextures(1, &texId[currentTexId]);
	glActiveTexture(getTexUnit(currentTexId));
	glBindTexture(GL_TEXTURE_2D, texId[currentTexId]);

	setTexParams(wrappingMode, filter);
	createTextureFromImage(imagePath, colorMode);

	currentTexId++;
}

void Texture::bind() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texId[0]);
}

void Texture::bind(const unsigned int texNum) {
	if (!texId[texNum]) {
		std::cout << "Invalid texNum to bind" << std::endl;
		return;
	}
	glActiveTexture(getTexUnit(texNum));
	glBindTexture(GL_TEXTURE_2D, texId[texNum]);
}

void Texture::createTextureFromImage(const std::string &imagePath, const GLenum colorMode) {
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(imagePath.c_str(), &width, &height, &nrChannels, 0);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, colorMode, width, height, 0, colorMode, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cout << "Failed to load texture: " << imagePath << std::endl;
	}

	stbi_image_free(data);
}

GLenum Texture::getTexUnit(const unsigned int n) {
	switch (n) {
		case 0: {
			return GL_TEXTURE0;
		}
		case 1: {
			return GL_TEXTURE1;
		}
		case 2: {
			return GL_TEXTURE2;
		}
		case 3: {
			return GL_TEXTURE3;
		}
		case 4: {
			return GL_TEXTURE4;
		}
		case 5: {
			return GL_TEXTURE5;
		}
		case 6: {
			return GL_TEXTURE6;
		}
		default: {
			std::cout << "TexUnit out of bounds" << std::endl;
		}
	}
}

void Texture::setTexParams(const GLenum wrappingMode, const GLenum filter) {
	// set texture wrapping / filtering options on currently bound texture object (texId)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrappingMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrappingMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
}