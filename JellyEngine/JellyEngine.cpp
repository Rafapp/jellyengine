/*
 * JELLYENGINE: Window, OS and runtime management (glfw). 
 */

// Core Libraries
#include <iostream>

// OpenGL Libraries
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Engine Components
#include "JellyEngine.h"

// Engine Renderer
Renderer renderer; // Engine renderer component
GLFWwindow* window; // GLFW window for rendering

// Engine Settings
int wWidth = 1280; // Window width
int wHeight = 720; // Window height

// Camera Settings
bool firstMouse = true; // Initial state for mouse movement logic

// Time Management
float deltaTime = 0.0f; // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
bool manualControlIsActive = false; // Default to manual control disabled
int selectedVertexIndex = 0; // Default to no selected vertex
bool isMToggled = false; // Default to manual control disabled

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
    

    // Toggle manual control
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS && !isMToggled) {
        manualControlIsActive = !manualControlIsActive;
        isMToggled = true;  // Prevent further toggling until the key is released
        std::cout << "Manual control is inactive" << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_RELEASE) {
        isMToggled = false;
    }

    // Move the selected vertex
    if (manualControlIsActive && selectedVertexIndex != -1) {
        float moveSpeed = 1.0f; // Speed at which the vertex will move

        Vertex& vertex = renderer.model->meshes[0].vertices[selectedVertexIndex];

        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            vertex.position.y += moveSpeed * deltaTime;
            std::cout << "UP" << std::endl;
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            vertex.position.y -= moveSpeed * deltaTime;
            std::cout << "DOWN" << std::endl;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
            std::
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
            vertex.position.x += moveSpeed * deltaTime;

        // Print the position of that vertex along with the vertex number
        std::cout << "Vertex " << selectedVertexIndex << ": " << vertex.position.x << ", " << vertex.position.y << ", " << vertex.position.z << std::endl;

        // Update the OpenGL buffer for the modified vertex
        glBindBuffer(GL_ARRAY_BUFFER, renderer.model->meshes[0].VBO); // Bind the VBO
        glBufferSubData(GL_ARRAY_BUFFER, renderer.model->meshes[0].vertices.size(), sizeof(Vertex), &vertex); // Update the buffer`
        glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind the VBO
    }

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
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSwapInterval(1);

    // Set up renderer
    renderer.setup(wWidth, wHeight);
    cout << "COMPLETE::OBJECTS SETUP" << endl;

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

    // Resize window
    glfwGetFramebufferSize(window, &wWidth, &wHeight);

    // Move light around
    renderer.light->p = glm::vec3(glm::cos(currentFrame) * 2.5f, 0.5f, glm::sin(currentFrame) * 2.5f);

    // ----------------- Update physics -----------------

    // Update the model matrix based on the model's position and scale
    renderer.model->modelMatrix = glm::translate(glm::mat4(1.0f), renderer.model->p)
       * glm::scale(glm::mat4(1.0f), renderer.model->s);

    
    // Now draw the scene after all updates
    renderer.draw(wWidth, wHeight);
    glfwSwapBuffers(window);
    glfwPollEvents();

    // "Squish" effect on model, if needed
    // renderer.model->s = glm::vec3(0.25f, 0.25f + (glm::abs(glm::sin(currentFrame * 0.0f)) * .025f), 0.25f);
}

/*
 * EXIT
 */
void shutdownEngine() {
    glfwDestroyWindow(window);
    glfwTerminate();
    std::cout << "EXIT::JELLY ENGINE QUIT" << std::endl;
}

int main() {
    if (setup() == -1) {
        return -1; // Ensure that setup is successful before proceeding
    }

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        update();
    }

    shutdownEngine(); // Clean shutdown
    return 0; // Return success
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

// Define the mouse button callback
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        // This is where you would determine which vertex the mouse is over, for simplicity here, toggle first vertex
        selectedVertexIndex = (selectedVertexIndex == -1) ? 0 : -1;
    }
}

// Define the conversion function (you'll need to implement this based on your view/projection)
glm::vec2 convertScreenToWorldCoords(double x, double y) {
    // Convert screen coordinates to normalized device coordinates
    float ndcX = (2.0f * x) / wWidth - 1.0f;
    float ndcY = 1.0f - (2.0f * y) / wHeight;
    glm::vec4 clipCoords = glm::vec4(ndcX, ndcY, -1.0f, 1.0f);

    // Get the view-projection matrix from the camera
    glm::mat4 projection = renderer.camera->GetProjectionMatrix(static_cast<float>(wWidth) / static_cast<float>(wHeight));
    glm::mat4 view = renderer.camera->GetViewMatrix();
    glm::mat4 viewProjection = projection * view;

    // Now invert the view-projection matrix
    glm::mat4 invVP = glm::inverse(viewProjection);
    glm::vec4 worldCoords = invVP * clipCoords;
    worldCoords /= worldCoords.w; // Perspective divide

    // Since we're working with a 2D quad in a 3D space, we don't need the z coordinate
    return glm::vec2(worldCoords.x, worldCoords.y);
}