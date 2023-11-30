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
     * SET UP GLFW, GLAD AND OPENGL: Todo ~ Make renderer class
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
     * BUFFERS: Todo ~ Make mesh class
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
     * MODEL: Todo ~ Make a model class 
     */
    glm::mat4 model = glm::mat4(1.0f);
    

    /*
     * CAMERA: Todo ~ Make camera class
     */

    // Camera attributes
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
    glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

    // View matrix
    glm::mat4 projection;
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)wWidth / (float)wHeight, 0.1f, 100.0f);

    // LookAt matrix
    glm::mat4 view;
    view = glm::lookAt(cameraPos, cameraTarget, up);

    // For fun, we can orbit the camera around!
    const float orbitRadius = 10;

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

        // Rotate camera
        float camX = sin(glfwGetTime()) * orbitRadius;
        float camZ = cos(glfwGetTime()) * orbitRadius;
        cameraPos = glm::vec3(camX, 0.0, camZ);
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f) * 0.001f, glm::vec3(0.5f, 1.0f, 0.5f));
        // Apply matrix transformations in shader
        int modelLoc = glGetUniformLocation(shader.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        int viewLoc = glGetUniformLocation(shader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        int projectionLoc = glGetUniformLocation(shader.ID, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

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
