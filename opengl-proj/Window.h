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
	unsigned int getWidth();
	unsigned int getHeight();

private:
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;

	unsigned int width;
	unsigned int height;
	GLFWwindow *window;

	inline static void framebufferSizeCallback(GLFWwindow *win, int w, int h) {
		Window *window = static_cast<Window*>(glfwGetWindowUserPointer(win));
		window->framebufferResize(w, h);
	}

	void framebufferResize(int width, int height);
};

#endif