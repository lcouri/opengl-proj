#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(GLFWwindow *window, glm::vec3 position, glm::vec3 worldUp, float yaw, float pitch)
	: window(window), position(position), worldUp(worldUp), yaw(yaw), pitch(pitch), front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), fov(FOV) {
	updateCameraVectors();
}

Camera::Camera(GLFWwindow *window, float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
	: window(window), position(glm::vec3(posX, posY, posZ)), worldUp(glm::vec3(upX, upY, upZ)), yaw(yaw), pitch(pitch), front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), fov(FOV) {
	updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() {
	return glm::lookAt(position, position + front, up);
}

void Camera::processKeyboardInput(Move direction, float deltaTime) {
	float camSpeed = SPEED * deltaTime;

	if (direction == Move::FORWARD) {
		position += camSpeed * front;
	}
	if (direction == Move::BACKWARD) {
		position -= camSpeed * front;
	}
	if (direction == Move::LEFT) {
		position -= camSpeed * right;
	}
	if (direction == Move::RIGHT) {
		position += camSpeed * right;
	}
}

void Camera::cursorPosCallback(double xpos, double ypos) {
	if (firstMouse) {
		lastX = (float)xpos;
		lastY = (float)ypos;
		firstMouse = false;
	}

	float xoffset = (float)xpos - lastX;
	float yoffset = lastY - (float)ypos; // reversed since y-coords range from bottom to top
	lastX = (float)xpos;
	lastY = (float)ypos;

	xoffset *= SENSITIVITY;
	yoffset *= SENSITIVITY;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f) {
		pitch = 89.0f;
	}
	if (pitch < -89.0f) {
		pitch = -89.0f;
	}

	updateCameraVectors();
}

void Camera::scrollCallback(double xoffset, double yoffset) {
	if (fov > 1.0f && fov <= 90.0f) {
		fov -= (float)yoffset;
	}
	if (fov <= 1.0f) {
		fov = 1.0f;
	}
	if (fov >= 90.0f) {
		fov = 90.0f;
	}
}

void Camera::updateCameraVectors() {
	// Calculate the new front vector
	glm::vec3 newFront;
	newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	newFront.y = sin(glm::radians(pitch));
	newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(newFront);

	// Also re-calc the right and up vector
	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}