#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
public:
	Window();

	GLFWwindow *getWindow();
	int shouldClose();
	void processInput();

private:
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;

	GLFWwindow *window;
};

#endif