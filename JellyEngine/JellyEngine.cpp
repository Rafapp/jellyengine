// Our code
#include "JellyEngine.h"
#include "shader.h"
#include "camera.h"

// Libraries
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

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
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = wWidth / 2.0f;
float lastY = wHeight / 2.0f;
bool firstMouse = true;

// Checks for key input
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// Callbacks a glfw error
static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

int main()
{
    /*
     * SET UP GLFW, GLAD AND OPENGL: Todo ~ Make renderer class
     */

    cout << "JELLY ENGINE: VERSION 1.0.0" << endl;
    cout << "Starting up ..." << endl;
    cout << endl;

    GLFWwindow* window;
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

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSwapInterval(1);

    /*
     * Shaders
     */
    Shader shader(RESOURCES_PATH "shaders/shader.vert", RESOURCES_PATH "shaders/shader.frag");

    /*
     * BUFFERS: Todo ~ Make mesh class
     */

     // Enable z-depth buffer
     glEnable(GL_DEPTH_TEST);

     // Vertices to draw, we use the indexed triangle data structure
    float vertices[] = {
        // positions         // colors
        -0.5f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
         0.5f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
         0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 2,   // first triangle
        2, 3, 1   // second triangle
    };

     // Create array buffer object
    unsigned int VBO;
    glGenBuffers(1, &VBO); // Create the buffer object with an ID
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // Bind to the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Copy to currently defined buffer

    // Creating a vertex array object (which is like a vbo, but natively calls glVertexAttribPointer, and glEnableVertexAttribArray)
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create an element buffer object (use the indexed triangle data structure)
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Specify data format, and location of first VERTEX (location = 0 in the vertex shader)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Specify data format, and location of first COLOR (location = 1 in the vertex shader) with a stride of 3
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Draw wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 

    /*
     * MODEL: Todo ~ Make a model class 
     */
    glm::mat4 model = glm::mat4(1.0f);

    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        // Update delta time
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Input
        processInput(window);

        float ratio;

        glfwGetFramebufferSize(window, &wWidth, &wHeight);
        ratio = wWidth / (float)wHeight;

        glViewport(0, 0, wWidth, wHeight); // TODO: This stretches things, we need to adjust the projection matrix

        // BG and clearing buffers
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Activate shader
        shader.use();

        // Projection matrix
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)wWidth / (float)wHeight, 0.1f, 100.0f);

        // View matrix
        glm::mat4 view = camera.GetViewMatrix();

        // Apply matrix transformations in shader
        int modelLoc = glGetUniformLocation(shader.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        int viewLoc = glGetUniformLocation(shader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        int projectionLoc = glGetUniformLocation(shader.ID, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        // Render the triangles
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
