#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
public:
	Window();

	GLFWwindow *getWindow();
	int shouldClose();
	unsigned int getWidth() { return width; };
	unsigned int getHeight() { return height; };

	void framebufferSizeCallback(int width, int height);
	void escapeKeyPress();

private:
	const unsigned int SCR_WIDTH = 1280;
	const unsigned int SCR_HEIGHT = 720;

	unsigned int width;
	unsigned int height;
	GLFWwindow *window;
};

#endif