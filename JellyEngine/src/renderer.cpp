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
    lightPos = glm::vec3(2.0f, 2.0f, 2.0f);
    glm::mat4 lT = glm::translate(lightTransform, lightPos);
    glm::mat4 lR = glm::rotate(lightTransform, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 lS = glm::scale(lightTransform, glm::vec3(0.25f, 0.25f, 0.25f));
    lightTransform = lT * lR * lS;

    model = new Model(RESOURCES_PATH "3D/dragon.obj");
    cout << "COMPLETE::MODEL LOADED" << endl;

    light = new Model(RESOURCES_PATH "3D/cube.obj");
    cout << "COMPLETE::LIGHT LOADED" << endl;

    /*
    * SHADERS
    */
    mainShader->use();
    
    //Draw wireframe (debugging)
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 

    // Enable openGL color/alpha blending.
    // the GPU combines the colors of multiple fragment
    // into a final output color
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    cout << "COMPLETE::RENDERER SETUP" << endl;
}

void Renderer::draw(float wWidth, float wHeight) {
    glViewport(0, 0, wWidth, wHeight);

    // BG and clearing buffers
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Projection matrix
    glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)wWidth / (float)wHeight, 0.1f, 100.0f);

    // View matrix
    glm::mat4 view = camera->GetViewMatrix();

    // Uniforms
    int transformLoc = glGetUniformLocation(mainShader->ID, "transform");
    int modelViewLoc = glGetUniformLocation(mainShader->ID, "view");
    int modelViewPosLoc = glGetUniformLocation(mainShader->ID, "viewPos");
    int modelProjectionLoc = glGetUniformLocation(mainShader->ID, "projection");
    int boolLoc = glGetUniformLocation(mainShader->ID, "calculateLighting");
    int colorLoc = glGetUniformLocation(mainShader->ID, "color");

    // Update light translate, send to uniform
    lightTransform = glm::mat4(1.0f);
    glm::mat4 lT = glm::translate(lightTransform, lightPos);
    glm::mat4 lR = glm::rotate(lightTransform, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 lS = glm::scale(lightTransform, glm::vec3(0.125f, 0.125f, 0.125f));
    lightTransform = lT * lR * lS;

    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(lightTransform));

    // Update light color, enable rendering calculations 
    glUniform3f(colorLoc, lightColor.x, lightColor.y, lightColor.z);
    glUniform1i(boolLoc, 0);

    int lightPosLoc = glGetUniformLocation(mainShader->ID, "lightPos");
    glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);// Set light position.
    light->draw(*mainShader);

    // Set object's transforms

    modelTransform = glm::mat4(1.0f);
    glm::mat4 mT = glm::translate(modelTransform, glm::vec3(0.0f, 0.0f, 0.0f));
    glm::mat4 mR = glm::rotate(modelTransform, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 mS = glm::scale(modelTransform, glm::vec3(0.25f, objectScaleY, 0.25f));
    modelTransform = mT * mR * mS;

    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(modelTransform));
    glUniformMatrix4fv(modelViewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(modelProjectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // Set object's color and view position for phong, enable rendering calculations
    glUniform3f(colorLoc, modelColor.x, modelColor.y, modelColor.z);
    glUniform3f(modelViewPosLoc, camera->Position.x, camera->Position.y, camera->Position.z);
    glUniform1i(boolLoc, 1);

    // Draw object
    model->draw(*mainShader);
}