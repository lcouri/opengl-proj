#include "Mesh.h"

//Mesh::Mesh(std::vector<float> vertices) {
//	this->vertices = vertices;
//
//	genVAO();
//	addVBO();
//}

Mesh::Mesh(std::vector<float> &vertices, std::vector<unsigned int> &indices) {
	genVAO();

	// position
	addVBO(vertices, 3, GL_FLOAT, 8);
	// colour
	addVBO(vertices, 3, GL_FLOAT, 8, 3);
	// tex uvs
	addVBO(vertices, 2, GL_FLOAT, 8, 6);

	addEBO(indices);
}

void Mesh::bind() {
	glBindVertexArray(vao);
}

void Mesh::deleteData() {
	if (vao) {
		glDeleteVertexArrays(1, &vao);
	}

	if (vbos.size() > 0) {
		glDeleteBuffers(vbos.size(), vbos.data());
	}

	if (ebo) {
		glDeleteBuffers(1, &ebo);
	}

	vbos.clear();
	vertexAttribPointerIndex = 0;
}

void Mesh::genVAO() {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
}

void Mesh::addVBO(const std::vector<float> &data, unsigned int dimensions, const GLenum type, const unsigned int stride, const unsigned int offset) {
	size_t elementSize = sizeof(*data.data());
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, data.size() * elementSize, data.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(vertexAttribPointerIndex, dimensions, type, GL_FALSE, stride * elementSize, (void*)(offset * elementSize));
	glEnableVertexAttribArray(vertexAttribPointerIndex);

	vertexAttribPointerIndex++;
	vbos.push_back(vbo);
}

void Mesh::addEBO(const std::vector<unsigned int> &indices) {
	size_t elementSize = sizeof(*indices.data());
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * elementSize, indices.data(), GL_STATIC_DRAW);
}