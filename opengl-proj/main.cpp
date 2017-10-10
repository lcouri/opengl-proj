#include <iostream>

#include "Shader.h"
#include "Window.h"

int main() {
	Window window = Window();

	glEnable(GL_DEPTH_TEST);

	// -----------shader setup--------------
	Shader shader = Shader();
	shader.addShader("vertexShader.glsl", GL_VERTEX_SHADER);
	shader.addShader("fragmentShader.glsl", GL_FRAGMENT_SHADER);

	// ------------vert setup---------------
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	shader.useProgram();

	// ------------Render loop--------------
	while (!window.shouldClose()) {
		// input
		window.processInput();

		// render stuff
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// poll events and swap buffers
		glfwPollEvents();
		glfwSwapBuffers(window.getWindow());
	}

	glfwTerminate();
	return 0;
}