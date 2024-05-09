/*
 * JELLYENGINE: Engine initialization and main loops
 */

#pragma once

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "renderer.h"
#include "camera.h"

// Window settings
static GLFWwindow* window;
static float targetAspectRatio = 16.0 / 9.0;
static int startWidth = 1920;
static int startHeight = 1080;

// Data
static float windowWidth = startWidth, windowHeight = startHeight;
static float scrollX, scrollY;
static float mouseX, mouseY;
static Model* light;
static vector<Model*> scene;

// Callbacks
static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
static void error_callback(int error, const char* description);

// Engine
class Engine {
public:
	template<typename Game>
	static int InitializeEngine() {
		std::cout << "INITIALIZING::JELLY ENGINE VERSION 1.0.0 ..." << std::endl;

		GLuint vertex_buffer, vertex_shader, fragment_shader, program;

		glfwSetErrorCallback(error_callback);

		if (!glfwInit()) {
			std::cerr << "Failed to initialize GLFW" << std::endl;
			glfwTerminate();
			return -1;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

		window = glfwCreateWindow(startWidth, startHeight, "Jelly Engine", nullptr, nullptr);

		if (!window) {
			std::cerr << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return -1;
		}

		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetScrollCallback(window, scroll_callback);

		// TODO: Make mouse locking a game.cpp feature
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Failed to initialize GLAD" << std::endl;
			return -1;
		}

		glfwSwapInterval(1);

		std::cout << "COMPLETE::JELLY ENGINE SETUP" << std::endl;
		std::cout << std::endl;

		std::cout << "INITIALIZING::RENDERER SETUP ..." << std::endl;
		Renderer::Setup();
		std::cout << "COMPLETE::RENDERER SETUP" << std::endl;
		std::cout << std::endl;

		Game game;
		game.Start();

		// Update
		while (!glfwWindowShouldClose(window)) {
			static float dt = 0.0;
			static float lastFrame = 0.0;
			static float currentFrame = 0.0;

			currentFrame = glfwGetTime();
			dt = currentFrame - lastFrame;
			lastFrame = currentFrame;

			// Update the camera
			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) Renderer::camera->ProcessKeyboard(FORWARD, dt);
			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) Renderer::camera->ProcessKeyboard(LEFT, dt);
			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) Renderer::camera->ProcessKeyboard(BACKWARD, dt);
			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) Renderer::camera->ProcessKeyboard(RIGHT, dt);
			if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) Renderer::camera->ResetPosition();

			Renderer::Draw(light, scene);

			glfwSwapBuffers(window);
			glfwPollEvents();

			game.Update(dt);
		}
	}

	virtual void Start() = 0;
	virtual void Update(float dt) = 0;
	virtual void Exit() = 0;
};

/*
 * CALLBACKS
 */

static void error_callback(int error, const char* description) {
	fprintf(stderr, "Error: %s\n", description);
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {

	// Aspect ratio calculations
	static float aspectRatio = (float)width / (float)height;
	int newWidth, newHeight;

	if (aspectRatio > targetAspectRatio) {
		newWidth = (int)(height * targetAspectRatio);
		newHeight = height;
	}
	else {
		newWidth = width;
		newHeight = (int)(width / targetAspectRatio);
	}

	// Calculate viewport position to center the scene
	int xOffset = (width - newWidth) / 2;
	int yOffset = (height - newHeight) / 2;

	// Set the viewport with letterboxing
	glViewport(xOffset, yOffset, newWidth, newHeight);

	windowWidth = width;
	windowHeight = height;
}

static bool firstMouse = true;
static void mouse_callback(GLFWwindow* window, double x, double y) {
	mouseX = static_cast<float>(x);
	mouseY = static_cast<float>(y);

	if (firstMouse)
	{
		Renderer::camera->lastX = mouseX;
		Renderer::camera->lastY = mouseY;
		firstMouse = false;
	}

	float xoffset = mouseX - Renderer::camera->lastX;
	float yoffset = Renderer::camera->lastY - mouseY; // reversed since y-coordinates go from bottom to top

	Renderer::camera->lastX = mouseX;
	Renderer::camera->lastY = mouseY;

	Renderer::camera->ProcessMouseMovement(xoffset, yoffset);
}

static void scroll_callback(GLFWwindow* window, double x, double y) {
	scrollX = x;
	scrollY = y;
	Renderer::camera->ProcessMouseScroll(static_cast<float>(y));
}


