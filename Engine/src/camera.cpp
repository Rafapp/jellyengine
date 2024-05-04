/*
 * CAMERA: Class for a perspective-accurate camera
 */

#include <iostream>

#include "camera.h"

using namespace std;

// TODO: Destructors

// Default constructor
Camera::Camera() {

	// World values
	Position = glm::vec3(1.0f, 0.0f, 1.0f);
	WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	Yaw = -90.0f;
	Pitch = 0.0f;

	// Control values
	Front = glm::vec3(0.0f, 0.0f, -1.0f);
	MovementSpeed = 1.5f;
	MouseSensitivity = 0.05f;
	Zoom = 45.0f;

	updateCameraVectors();
}

// Constructor with vectors
Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) {

	// World values
	Position = position;
	WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;

	// Control values
	Front = glm::vec3(0.0f, 0.0f, -1.0f);
	MovementSpeed = 2.5f;
	MouseSensitivity = 0.05f;
	Zoom = 45.0f;

	updateCameraVectors();
}

// returns the view matrix calculated using Euler Angles and the LookAt Matrix
glm::mat4 Camera::GetViewMatrix() { return glm::lookAt(Position, Position + Front, Up); }

// processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime) {
	float velocity = MovementSpeed * deltaTime;
	if (direction == FORWARD)
		Position += Front * velocity;
	if (direction == BACKWARD)
		Position -= Front * velocity;
	if (direction == LEFT)
		Position -= Right * velocity;
	if (direction == RIGHT)
		Position += Right * velocity;
}

// processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}

	// update Front, Right and Up Vectors using the updated Euler angles
	updateCameraVectors();
	std::cout << Pitch << std::endl;
}

// processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void Camera::ProcessMouseScroll(float y) {
	std::cout << "Processing mouse scroll" << std::endl;
	Zoom -= (float)y;
	if (Zoom < 1.0f)
		Zoom = 1.0f;
	if (Zoom > 45.0f)
		Zoom = 45.0f;
}

// calculates the front vector from the Camera's (updated) Euler Angles
void Camera::updateCameraVectors() {
	// calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(front);
	// also re-calculate the Right and Up vector
	Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	Up = glm::normalize(glm::cross(Right, Front));
}

void Camera::ResetPosition() {
	Position = glm::vec3(0.0f);
}