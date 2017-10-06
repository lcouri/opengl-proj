#ifndef SHADER_H
#define SHADER_H

#include "FileUtil.h"

#include <glad/glad.h>

#include <string>
#include <iostream>

class Shader {
public:
	Shader();

	void addShader(const std::string &shaderPath, const GLenum type);
	void useProgram();
	void setUniform(const std::string &name, float v1, float v2, float v3, float v4);
	void setUniform(const std::string &name, float v1);
	void setUniform(const std::string &name, int v1);
	void setUniform(const std::string &name, const GLfloat *v1);

private:
	int shaderProgram;

	void checkForShaderErrors(unsigned int id, std::string path);
	void checkForLinkErrors();
};

#endif