#include "Shader.h"

#include "FileUtil.h"

Shader::Shader(const std::string &shaderPath, const GLenum type) {
	this->shaderPath = shaderPath;
	shaderSource = readFileToString(shaderPath);
	const char *shaderSource_cstr = shaderSource.c_str();

	shaderID = glCreateShader(type);
	glShaderSource(shaderID, 1, &shaderSource_cstr, NULL);
}

unsigned int Shader::getID() {
	return shaderID;
}

std::string Shader::getPath() {
	return shaderPath;
}

std::string Shader::getSource() {
	return shaderSource;
}