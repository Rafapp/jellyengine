/*
 * RENDERER: OpenGL rendering backend
 */

#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <renderer.h>

using namespace std;

void Renderer::setup(float wWidth, float wHeight) {
    /*
     * SETUP
     */

	// Set up camera
	camera = new Camera();
	float lastX = wWidth / 2.0f;
	float lastY = wHeight / 2.0f;

	// Set up gummy shader and light shader
	mainShader = new Shader(RESOURCES_PATH "shaders/shader.vert", RESOURCES_PATH "shaders/shader.frag");

    /*
     * BUFFERS
     */

    // Enable z-depth buffer
    glEnable(GL_DEPTH_TEST);

    /*
     * MODELS: TODO ~ Have channels per-model, and a getTransform() function
     */

    modelTransform = glm::mat4(1.0f);
    glm::mat4 mT = glm::translate(modelTransform, glm::vec3(0.0f, 0.0f, 0.0f));
    glm::mat4 mR = glm::rotate(modelTransform, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 mS = glm::scale(modelTransform, glm::vec3(0.25f, 0.25f, 0.25f));
    modelTransform = mT * mR * mS;

    lightTransform = glm::mat4(1.0f);
    glm::mat4 lT = glm::translate(lightTransform, glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 lR = glm::rotate(lightTransform, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 lS = glm::scale(lightTransform, glm::vec3(0.25f, 0.25f, 0.25f));
    lightTransform = lT * lR * lS;

    model = new Model(RESOURCES_PATH "3D/gummybear.fbx");
    cout << "COMPLETE::MODEL LOADED" << endl;

    light = new Model(RESOURCES_PATH "3D/cube.obj");
    cout << "COMPLETE::LIGHT LOADED" << endl;

    /*
    * SHADERS
    */
    mainShader->use();
    
    //Draw wireframe (debugging)
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 

    cout << "COMPLETE::RENDERER SETUP" << endl;
}

void Renderer::draw(float wWidth, float wHeight) {
    glViewport(0, 0, wWidth, wHeight); // TODO: This stretches things, we need to adjust the projection matrix

    // BG and clearing buffers
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Projection matrix
    glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)wWidth / (float)wHeight, 0.1f, 100.0f);

    // View matrix
    glm::mat4 view = camera->GetViewMatrix();

    // Model uniforms
    int modelLoc = glGetUniformLocation(mainShader->ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelTransform));

    int modelViewLoc = glGetUniformLocation(mainShader->ID, "view");
    glUniformMatrix4fv(modelViewLoc, 1, GL_FALSE, glm::value_ptr(view));

    int modelProjectionLoc = glGetUniformLocation(mainShader->ID, "projection");
    glUniformMatrix4fv(modelProjectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // Draw the model with its color
    int colorLoc = glGetUniformLocation(mainShader->ID, "color");
    glUniform3f(colorLoc, modelColor.x, modelColor.y, modelColor.z);
    model->draw(*mainShader);

    // Update light translate
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(lightTransform));

    // Draw the light with its 
    glUniform3f(colorLoc, lightColor.x, lightColor.y, lightColor.z);
    light->draw(*mainShader);
    
}