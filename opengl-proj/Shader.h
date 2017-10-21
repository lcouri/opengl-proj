#ifndef SHADER_H
#define SHADER_H

#include <string>

#include <glad/glad.h>

class Shader {
public:
	Shader(const std::string &shaderPath, const GLenum type);

	unsigned int getID();
	std::string getPath();
	std::string getSource();

private:
	unsigned int shaderID;
	std::string shaderPath;
	std::string shaderSource;
};

#endif