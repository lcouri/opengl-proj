#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include "Shader.h"

#include <string>
#include <glad/glad.h>

class ShaderProgram {
public:
	ShaderProgram();

	void addShader(Shader shader);
	void addShader(const std::string &shaderPath, const GLenum type);
	void use();
	void setUniform(const std::string &name, float v1, float v2, float v3, float v4);
	void setUniform(const std::string &name, float v1);
	void setUniform(const std::string &name, int v1);
	void setUniform(const std::string &name, const GLfloat *v1);

private:
	int shaderProgram;

	void checkForLinkErrors();
	void checkForShaderErrors(unsigned int id, std::string path);
};

#endif
