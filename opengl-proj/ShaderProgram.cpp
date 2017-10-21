#include "ShaderProgram.h"

#include <iostream>

#include "FileUtil.h"

ShaderProgram::ShaderProgram() {
	shaderProgram = glCreateProgram();
}

void ShaderProgram::addShader(Shader shader) {
	glCompileShader(shader.getID());
	checkForShaderErrors(shader.getID(), shader.getPath());

	glAttachShader(shaderProgram, shader.getID());
	glLinkProgram(shaderProgram);
	checkForLinkErrors();

	glDeleteShader(shader.getID());
}

void ShaderProgram::addShader(const std::string &shaderPath, const GLenum type) {
	Shader shader = Shader(shaderPath, type);
	addShader(shader);
}

void ShaderProgram::use() {
	glUseProgram(shaderProgram);
}

void ShaderProgram::setUniform(const std::string &name, float v1, float v2, float v3, float v4) {
	glUniform4f(glGetUniformLocation(shaderProgram, name.c_str()), v1, v2, v3, v4);
}

void ShaderProgram::setUniform(const std::string &name, float v1) {
	glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), v1);
}

void ShaderProgram::setUniform(const std::string &name, int v1) {
	glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), v1);
}

void ShaderProgram::setUniform(const std::string &name, const GLfloat *v1) {
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, v1);
}

void ShaderProgram::checkForShaderErrors(unsigned int id, std::string path) {
	int success;
	char infoLog[512];

	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::" << path << "::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void ShaderProgram::checkForLinkErrors() {
	int success;
	char infoLog[512];

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
}