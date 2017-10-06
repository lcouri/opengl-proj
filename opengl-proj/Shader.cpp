#include "Shader.h"

Shader::Shader() {
	shaderProgram = glCreateProgram();
}

void Shader::addShader(const std::string &shaderPath, const GLenum type) {
	std::string shaderSource_str = readFileToString(shaderPath);
	const char *shaderSource = shaderSource_str.c_str();

	unsigned int shader = glCreateShader(type);
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);
	checkForShaderErrors(shader, shaderPath);

	glAttachShader(shaderProgram, shader);
	glLinkProgram(shaderProgram);
	checkForLinkErrors();

	glDeleteShader(shader);
}

void Shader::useProgram() {
	glUseProgram(shaderProgram);
}

void Shader::setUniform(const std::string &name, float v1, float v2, float v3, float v4) {
	glUniform4f(glGetUniformLocation(shaderProgram, name.c_str()), v1, v2, v3, v4);
}

void Shader::setUniform(const std::string &name, float v1) {
	glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), v1);
}

void Shader::setUniform(const std::string &name, int v1) {
	glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), v1);
}

void Shader::setUniform(const std::string &name, const GLfloat *v1) {
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, v1);
}

void Shader::checkForShaderErrors(unsigned int id, std::string path) {
	int success;
	char infoLog[512];

	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::" << path << "::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void Shader::checkForLinkErrors() {
	int success;
	char infoLog[512];

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

}