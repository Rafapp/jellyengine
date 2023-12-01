/*
 * RENDERER: OpenGL rendering backend
 */

#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <renderer.h>
#include <camera.h>
#include <renderer.h>
#include <shader.h>

using namespace std;

Renderer::setup() {
    /*
     * SETUP
     */

	// Set up camera
	camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	float lastX = wWidth / 2.0f;
	float lastY = wHeight / 2.0f;

	// Set up main shader
	mainShader = new Shader(RESOURCES_PATH "shaders/shader.vert", RESOURCES_PATH "shaders/shader.frag");

    /*
     * TEST OBJECT
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

    /*
     * BUFFERS
     */

    // Enable z-depth buffer
    glEnable(GL_DEPTH_TEST);

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
}

void Renderer::draw() {
    glViewport(0, 0, wWidth, wHeight); // TODO: This stretches things, we need to adjust the projection matrix

    // BG and clearing buffers
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Activate shader
    renderer.mainShader.use();

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
}