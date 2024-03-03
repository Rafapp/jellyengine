/*
 * JELLYENGINE: Window, OS and runtime management (glfw). 
 */

#include <iostream>

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "camera.h"
#include "JellyEngine.h"

Renderer renderer;
GLFWwindow* window;

// Functions
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// Delta time
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

// Settings
int wWidth = 1280;
int wHeight = 720;

// Camera 
bool firstMouse = true;

// Checks for key input
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        renderer.camera->ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        renderer.camera->ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        renderer.camera->ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        renderer.camera->ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        renderer.camera->ResetPosition();
}

// Callbacks a glfw error
static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

// Assuming you have a function to create vertices from Model data
std::vector<Vertex> modelToVertices(Model& model) {
    std::vector<Vertex> vertices;
    // Convert model data to Vertex struct used by Object
    // ...
    return vertices;
}

/*
 * SET UP GLFW, GLAD AND OPENGL
 */
int setup() {
    cout << "JELLY ENGINE: VERSION 1.0.0" << endl;
    cout << "Starting up ..." << endl;
    cout << endl;
    
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

    // Set up renderer
    renderer.setup(wWidth, wHeight);

    // Set up objects TODO: This would be parsed from a json/YAML
    cout << "COMPLETE::JELLY ENGINE SETUP" << endl;
}

/*
 * UPDATE
 */
void update() {
    // Update delta time
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // Input
    processInput(window);

    glfwGetFramebufferSize(window, &wWidth, &wHeight);

    // Move light around
    renderer.light->p = glm::vec3(glm::cos(currentFrame) * 2.5f, 0.5f, glm::sin(currentFrame) * 2.5f);
    renderer.draw(wWidth, wHeight);

    glfwSwapBuffers(window);
    glfwPollEvents();

    // "Squish" effect on model
    renderer.model->s = glm::vec3(0.25f, 0.25f + (glm::abs(glm::sin(currentFrame * 0.0f)) * .025f), 0.25f);
}

/*
 * EXIT
 */
void exit() {
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
    cout << "EXIT::JELLY ENGINE QUIT" << endl;
}

int main()
{
    setup();

    // Runtime loop
    while (!glfwWindowShouldClose(window))
    {
        update();
    }

    exit();

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        renderer.camera->lastX = xpos;
        renderer.camera->lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - renderer.camera->lastX;
    float yoffset = renderer.camera->lastY - ypos; // reversed since y-coordinates go from bottom to top

    renderer.camera->lastX = xpos;
    renderer.camera->lastY = ypos;

    renderer.camera->ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    renderer.camera->ProcessMouseScroll(static_cast<float>(yoffset));
}
