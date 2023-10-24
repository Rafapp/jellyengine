// JellyEngine.cpp : Defines the entry point for the application.
//

#include "JellyEngine.h"
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

int main()
{
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Set GLFW to not create an OpenGL context
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(800, 600, "GLFW Window", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

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
