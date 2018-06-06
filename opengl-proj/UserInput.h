#ifndef  USERINPUT_H
#define USERINPUT_H

#include "Window.h"
#include "Camera.h"

/*
Quick and dirty hack to get input from glfw and call the appropriate Window and Camera
functions.
#TODO
Replace this with a proper event handling system, where each class can register an
event to listen to and use their own callback without having to worry about the difference
between C and C++ callbacks.
Hopefully I'll it before this gets too out of hand, and I have a good solution.
*/
class UserInput {
public:
	UserInput(Window *window, Camera *camera);

	void processInput(float deltaTime);

private:
	GLFWwindow *GLFWwin;
	Window *window;
	Camera *camera;

	inline static void framebufferSizeCallback(GLFWwindow *win, int w, int h) {
		UserInput *userInput = static_cast<UserInput*>(glfwGetWindowUserPointer(win));
		if (userInput->window) {
			userInput->window->framebufferSizeCallback(w, h);
		}
	}

	inline static void cursorPosCallback(GLFWwindow *win, double xpos, double ypos) {
		UserInput *userInput = static_cast<UserInput*>(glfwGetWindowUserPointer(win));
		if (userInput->camera) {
			userInput->camera->cursorPosCallback(xpos, ypos);
		}
	}

	inline static void scrollCallback(GLFWwindow *win, double xoffset, double yoffset) {
		UserInput *userInput = static_cast<UserInput*>(glfwGetWindowUserPointer(win));
		if (userInput->camera) {
			userInput->camera->scrollCallback(xoffset, yoffset);
		}
	}
};

#endif