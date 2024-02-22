/*
 * RENDERER: OpenGL rendering backend
 */

#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "renderer.h"

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

    // Enable openGL color/alpha blending.
    // the GPU combines the colors of multiple fragment
    // into a final output color (allows transparency)
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    model = new Model(RESOURCES_PATH "3D/cube.obj");
    model->color = glm::vec3(0.0f, 1.0f, 0.0f);
    model->s = glm::vec3(1.0f);
    model->p = glm::vec3(0.0f, 1.0f, 0.0f);
    cout << "COMPLETE::MODEL LOADED" << endl;

    light = new Model(RESOURCES_PATH "3D/cube.obj");
    light->color = glm::vec3(1.0f, 1.0f, 1.0f);
    light->s = glm::vec3(0.125f, 0.125f, 0.125f);
    cout << "COMPLETE::LIGHT LOADED" << endl;

    plane = new Model(RESOURCES_PATH "3D/plane.obj");
    plane->color = glm::vec3(0.0f, 0.0f, 1.0f);
    plane->p = glm::vec3(0.0f, -0.25f, 0.0f);
    plane->s = glm::vec3(5.0f, -1.0f, 5.0f);

    /*
    * SHADERS
    */
    mainShader->use();
    
    //Draw wireframe (debugging)
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 

    cout << "COMPLETE::RENDERER SETUP" << endl;
}

void Renderer::draw(float wWidth, float wHeight) {
    glViewport(0, 0, wWidth, wHeight);

    // BG and clearing buffers
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(light->getTransform()));

    // Update light color, enable rendering calculations 
    glUniform3f(colorLoc, light->color.x, light->color.y, light->color.z);
    glUniform1i(boolLoc, 0);

    int lightPosLoc = glGetUniformLocation(mainShader->ID, "lightPos");
    glUniform3f(lightPosLoc, light->p.x, light->p.y, light->p.z);// Set light position.
    light->draw(*mainShader);

    // TODO: For loop the hell out of the stuff under here with a vector and Scene
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model->getTransform()));
    glUniformMatrix4fv(modelViewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(modelProjectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // Send model data
    glUniform3f(colorLoc, model->color.x, model->color.y, model->color.z);
    glUniform3f(modelViewPosLoc, camera->Position.x, camera->Position.y, camera->Position.z);
    glUniform1i(boolLoc, 1);

    // Render model
    model->draw(*mainShader);

    // Send plane position
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(plane->getTransform()));
    glUniformMatrix4fv(modelViewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(modelProjectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // Send plane data ~ TODO: Streamline this for an arbitrary amount of objects
    glUniform3f(colorLoc, plane->color.x, plane->color.y, plane->color.z);
    glUniform3f(modelViewPosLoc, camera->Position.x, camera->Position.y, camera->Position.z);
    glUniform1i(boolLoc, 1);

    // Render plane
    plane->draw(*mainShader);
}