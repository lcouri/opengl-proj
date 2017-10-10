#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <iostream>

#include <glad/glad.h>

#include "stb_image.h"

class Texture {
public:
	Texture();

	void addTextureUnit(const std::string &imagePath, const GLenum colorMode);
	void addTextureUnit(const std::string &imagePath, const GLenum colorMode, const GLenum wrappingMode);
	void addTextureUnit(const std::string &imagePath, const GLenum colorMode, const GLenum wrappingMode, const GLenum filter);
	void bind();
	void bind(const unsigned int texNum);

private:
	unsigned int texId[6];
	unsigned int currentTexId;

	void createTextureFromImage(const std::string &imagePath, const GLenum colorMode);
	void setTexParams(const GLenum wrappingMode, const GLenum filter);
	GLenum getTexUnit(const unsigned int n);
};

#endif