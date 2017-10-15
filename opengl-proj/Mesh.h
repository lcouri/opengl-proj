#ifndef MESH_H
#define MESH_H

#include <vector>
#include <glad/glad.h>

class Mesh {
public:
	Mesh(std::vector<float> &vertices);
	Mesh(std::vector<float> &vertices, std::vector<unsigned int> &indices);

	void bind();
	void deleteData();

private:
	unsigned int vao;
	std::vector<unsigned int> vbos;
	unsigned int vertexAttribPointerIndex;
	unsigned int ebo;

	void genVAO();
	void addVBO(const std::vector<float> &data, const unsigned int dimensions, const unsigned int stride = 0, const unsigned int offset = 0, const GLenum type = GL_FLOAT);
	void addEBO(const std::vector<unsigned int> &indices);
};

#endif