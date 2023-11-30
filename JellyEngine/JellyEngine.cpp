// Our code
#include "JellyEngine.h"
#include "shader.h"

// Libraries
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <iostream>


using namespace std;

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
    /*
     * SET UP GLFW, GLAD AND OPENGL
     */

    cout << "JELLY ENGINE: VERSION 1.0.0" << endl;
    cout << "Starting up ..." << endl;
    cout << endl;

    GLFWwindow* window;
    GLuint vertex_buffer, vertex_shader, fragment_shader, program;
    GLint wWidth = 1280, wHeight = 720;

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

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSwapInterval(1);

    glfwSetKeyCallback(window, key_callback);

    /*
     * Shaders
     */
    Shader shader(RESOURCES_PATH "shaders/shader.vert", RESOURCES_PATH "shaders/shader.frag");

    /*
     * BUFFERS
     */

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
     * CAMERA 
     */
     
    // View matrix
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); // Camera's position

    // Projection matrix
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);


    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        float ratio;

        glfwGetFramebufferSize(window, &wWidth, &wHeight);
        ratio = wWidth / (float)wHeight;

        glViewport(0, 0, wWidth, wHeight); // TODO: This stretches things, we need to adjust the projection matrix

        // BG Color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Activate shader
        shader.use();

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
