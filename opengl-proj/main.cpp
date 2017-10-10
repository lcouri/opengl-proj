#include <iostream>

#include "Shader.h"
#include "Window.h"
#include "Texture.h"

int main() {
	Window window = Window();

	glEnable(GL_DEPTH_TEST);

	// -----------shader setup--------------
	Shader shader = Shader();
	shader.addShader("vertexShader.glsl", GL_VERTEX_SHADER);
	shader.addShader("fragmentShader.glsl", GL_FRAGMENT_SHADER);

	// ------------vert setup---------------
	float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
	};
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// texture
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	Texture texture = Texture();
	texture.addTextureUnit("Texture/container.jpg", GL_RGB);
	texture.addTextureUnit("Texture/awesomeface.png", GL_RGBA);

	shader.useProgram();
	shader.setUniform("texture1", 0);
	shader.setUniform("texture2", 1);

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

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// poll events and swap buffers
		glfwPollEvents();
		glfwSwapBuffers(window.getWindow());
	}

	//----------de-allocate resources---------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}