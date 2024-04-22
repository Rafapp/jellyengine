/*
 * JELLYENGINE: Engine initialization and main loops
 */

#pragma once

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "renderer.h"

// Window settings
static GLFWwindow* window;
static int startWidth = 1280;
static int startHeight = 720;

// Data
static float windowWidth = startWidth, windowHeight = startHeight;
static float scrollX, scrollY;
static float mouseX, mouseY;

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

		// Uncomment this if you'd like to show the mouse
		// glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Failed to initialize GLAD" << std::endl;
			return -1;
		}

		glfwSwapInterval(1);

		std::cout << "COMPLETE::JELLY ENGINE SETUP" << std::endl;
		std::cout << std::endl;

		std::cout << "INITIALIZING::RENDERER SETUP ..." << std::endl;
		RendererSetup();
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
			/*if (keyPressed("w")) Renderer::camera->ProcessKeyboard(FORWARD, dt);
			if (keyPressed("a")) Renderer::camera->ProcessKeyboard(FORWARD, dt);
			if (keyPressed("s")) Renderer::camera->ProcessKeyboard(FORWARD, dt);
			if (keyPressed("d")) Renderer::camera->ProcessKeyboard(FORWARD, dt);
			if (keyPressed("r")) Renderer::camera->ResetPosition();*/

			RendererDraw();

			glfwSwapBuffers(window);
			glfwPollEvents();

			game.Update(dt);
		}
	}

	virtual void Start() = 0;
	virtual void Update(float dt) = 0;
	virtual void Exit() = 0;
	virtual void Draw() = 0;
};

/*
 * CALLBACKS
 */

static void error_callback(int error, const char* description) {
	fprintf(stderr, "Error: %s\n", description);
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	windowWidth = width;
	windowHeight = height;
	glViewport(0, 0, width, height);
}

static void mouse_callback(GLFWwindow* window, double x, double y) {
	mouseX = static_cast<float>(x);
	mouseY = static_cast<float>(y);
	// FIX: Renderer::camera is nullptr
	//Renderer::camera->ProcessMouseMovement(x, y);
}

static void scroll_callback(GLFWwindow* window, double x, double y) {
	scrollX = x;
	scrollY = y;
	// FIX: Renderer::camera is nullptr
	// Renderer::camera->ProcessMouseScroll(static_cast<float>(y));
}


