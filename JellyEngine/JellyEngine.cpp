#include "JellyEngine.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


using namespace std;

GLint SCREEN_WIDTH = 1280, SCREEN_HEIGHT = 720;

// Callbacks a glfw error
static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

// Checks for key input
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        cout << "ESC has been pressed." << endl;
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int main()
{
    GLFWwindow* window;

    // Set error callback, in case we encounter any errors
    glfwSetErrorCallback(error_callback);

    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Require minimum OpenGL version 0
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    // Create a window
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Jelly Engine", nullptr, nullptr);

    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Assign a openGL context (Assign memory in OS for openGL computations)
    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Add our esc input to the glfw process
    glfwSetKeyCallback(window, key_callback);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        // Poll for and process events
        glfwPollEvents();
    }

    // Destroy the window and terminate GLFW
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;

}

