#include <iostream>

#include "ShaderProgram.h"
#include "Shader.h"
#include "Window.h"
#include "Texture.h"
#include "Mesh.h"

int main() {
	Window window = Window();

	glEnable(GL_DEPTH_TEST);

	// -----------shader setup--------------
	ShaderProgram shaderProgram = ShaderProgram();
	shaderProgram.addShader("vertexShader.glsl", GL_VERTEX_SHADER);
	shaderProgram.addShader("fragmentShader.glsl", GL_FRAGMENT_SHADER);

	// ------------vert setup---------------
	std::vector<float> vertices = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
	};
	std::vector<unsigned int> indices = {
		0, 1, 3,
		1, 2, 3
	};

	Mesh mesh = Mesh(vertices, indices);

	Texture texture = Texture();
	texture.addTextureUnit("Texture/container.jpg", GL_RGB);
	texture.addTextureUnit("Texture/awesomeface.png", GL_RGBA);

	shaderProgram.use();
	shaderProgram.setUniform("texture1", 0);
	shaderProgram.setUniform("texture2", 1);

	// ------------Render loop--------------
	while (!window.shouldClose()) {
		// input
		window.processInput();

		// render stuff
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// bind textures
		texture.bind(0);
		texture.bind(1);

		//mesh.bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// poll events and swap buffers
		glfwPollEvents();
		glfwSwapBuffers(window.getWindow());
	}

	//----------de-allocate resources---------
	mesh.deleteData();

	glfwTerminate();
	return 0;
}