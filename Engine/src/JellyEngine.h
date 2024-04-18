/*
 * JELLYENGINE: Engine initialization and main loops
 */

#pragma once

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace Renderer {
	void Setup();
}

// Window settings
GLFWwindow* window;
int wWidth = 1280;
int wHeight = 720;

// Callbacks
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
static void error_callback(int error, const char* description);

// Engine
class Engine {
public:
	template<typename Game>
	static void InitializeEngine() {
		std::cout << "JELLY ENGINE: VERSION 1.0.0" << std::endl;
		std::cout << "Starting ..." << std::endl;

		GLuint vertex_buffer, vertex_shader, fragment_shader, program;

		glfwSetErrorCallback(error_callback);

		if (!glfwInit()) {
			std::cerr << "Failed to initialize GLFW" << std::endl;
			glfwTerminate();
			return -1;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

		window = glfwCreateWindow(wWidth, wHeight, "Jelly Engine", nullptr, nullptr);

		if (!window) {
			std::cerr << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return -1;
		}

		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetScrollCallback(window, scroll_callback);

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return -1;
		}

		glfwSwapInterval(1);

		std::cout << "COMPLETE::JELLY ENGINE SETUP" << std::endl;

		/*
		Renderer::Setup();

		Game game;
		game.Start();

		std::cout << "Press any key to continue...";
		std::cin.get();
		int i = 0;
		// GLFW loop
		while (true) {
			float dt = 0;
			game.Update(dt);
			game.Draw();
			i++;
			if (i > 10) break;
		}
		game.Exit();
		*/
	}
	virtual void Start() = 0;
	virtual void Update(float dt) = 0;
	virtual void Exit() = 0;
	virtual void Draw() = 0;
};

/*
 * CALLBACKS
 */

static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{

}


