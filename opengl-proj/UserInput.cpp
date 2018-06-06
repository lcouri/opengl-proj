#include "UserInput.h"

UserInput::UserInput(Window *window, Camera *camera)
	: window(window), GLFWwin(window->getWindow()), camera(camera) {
	// set user pointer so callbacks can reference this object
	glfwSetWindowUserPointer(GLFWwin, this);

	// set callbacks
	glfwSetFramebufferSizeCallback(GLFWwin, framebufferSizeCallback);
	glfwSetCursorPosCallback(GLFWwin, cursorPosCallback);
	glfwSetScrollCallback(GLFWwin, scrollCallback);
}

void UserInput::processInput(float deltaTime) {
	if (glfwGetKey(GLFWwin, GLFW_KEY_W) == GLFW_PRESS) {
		camera->processKeyboardInput(Move::FORWARD, deltaTime);
	}
	if (glfwGetKey(GLFWwin, GLFW_KEY_S) == GLFW_PRESS) {
		camera->processKeyboardInput(Move::BACKWARD, deltaTime);
	}
	if (glfwGetKey(GLFWwin, GLFW_KEY_A) == GLFW_PRESS) {
		camera->processKeyboardInput(Move::LEFT, deltaTime);
	}
	if (glfwGetKey(GLFWwin, GLFW_KEY_D) == GLFW_PRESS) {
		camera->processKeyboardInput(Move::RIGHT, deltaTime);
	}

	if (glfwGetKey(GLFWwin, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		window->escapeKeyPress();
	}
}