#include "Mesh.h"

Mesh::Mesh() {
	genVAO();
}

void Mesh::bind() {
	glBindVertexArray(vao);
}

void Mesh::deleteData() {
	if (vao) {
		glDeleteVertexArrays(1, &vao);
	}

	if (vbos.size() > 0) {
		glDeleteBuffers((GLsizei)vbos.size(), vbos.data());
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

unsigned int Mesh::addVBO(const std::vector<float> &data, unsigned int dimensions, const unsigned int stride, const unsigned int offset, const GLenum type) {
	size_t elementSize = sizeof(*data.data());
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, data.size() * elementSize, data.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(vertexAttribPointerIndex, dimensions, type, GL_FALSE, stride * (GLsizei)elementSize, (void*)(offset * elementSize));
	glEnableVertexAttribArray(vertexAttribPointerIndex);

	vertexAttribPointerIndex++;
	vbos.push_back(vbo);

	return vbo;
}

void Mesh::addVBO(const unsigned int vbo, const unsigned int dimensions, size_t elementSize, const unsigned int stride, const unsigned int offset, const GLenum type) {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glVertexAttribPointer(vertexAttribPointerIndex, dimensions, type, GL_FALSE, stride * (GLsizei)elementSize, (void*)(offset * elementSize));

	vertexAttribPointerIndex++;
	vbos.push_back(vbo);
}

void Mesh::addEBO(const std::vector<unsigned int> &indices) {
	size_t elementSize = sizeof(*indices.data());
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * elementSize, indices.data(), GL_STATIC_DRAW);
}