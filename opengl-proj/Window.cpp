#include "Window.h"

Window::Window() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// ---------GLFW window creation--------
	width = SCR_WIDTH;
	height = SCR_HEIGHT;
	window = glfwCreateWindow(width, height, "opengl-proj", NULL, NULL);

	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	// ------------GLAD init----------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialise GLAD" << std::endl;
	}

	glfwSetWindowUserPointer(window, this);
}

unsigned int Window::getWidth() {
	return width;
}
unsigned int Window::getHeight() {
	return height;
}

int Window::shouldClose() {
	return glfwWindowShouldClose(window);
}

GLFWwindow *Window::getWindow() {
	return window;
}

void Window::processInput() {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

void Window::framebufferResize(int width, int height) {
	glViewport(0, 0, width, height);
	this->width = width;
	this->height = height;
}