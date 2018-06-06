#ifndef MESH_H
#define MESH_H

#include <vector>
#include <glad/glad.h>

/*
So this class essentially deals with VAOs. On construction it generates a VAO, and from there you
can in theory add VBOs and EBOs as you wish.

#TODO
-Make sure the VAO is bound before adding any Buffer Objects.
-Maybe VBOs need their own class to store glVertexAttribPointer info about itself?
*/
class Mesh {
public:
	Mesh();

	void bind();

	// Generates and adds a VBO to this Mesh's VAO, returning the VBO id in case you want to use it elsewhere.
	unsigned int addVBO(const std::vector<float> &data, const unsigned int dimensions, const unsigned int stride = 0, const unsigned int offset = 0, const GLenum type = GL_FLOAT);

	// Adds an existing VBO to this Mesh's VAO
	void addVBO(const unsigned int vbo, const unsigned int dimensions, const size_t elementSize, const unsigned int stride = 0, const unsigned int offset = 0, const GLenum type = GL_FLOAT);

	void deleteData();

private:
	unsigned int vao;
	std::vector<unsigned int> vbos;
	unsigned int vertexAttribPointerIndex;
	unsigned int ebo;

	void genVAO();

	void addEBO(const std::vector<unsigned int> &indices);
};

#endif