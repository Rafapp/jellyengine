/*
 * RENDERER: Singleton that handles OpenGL draw calls
 */

#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "jellyEngine.h"
#include "renderer.h"

namespace Renderer {
    Camera* camera;
    Shader* shader;
    Model* model;
    Model* light;
    Model* plane;

    void Renderer::Setup() {
        camera = new Camera();
        float lastX = windowWidth / 2.0;
        float lastY = windowHeight / 2.0;

        // Set up gummy shader
        shader = new Shader(RESOURCES_PATH "shaders/shader.vert", RESOURCES_PATH "shaders/shader.frag");

        // Enable z-depth buffer
        glEnable(GL_DEPTH_TEST);

        // TRANSPARENT TODO: Make drawing in wireframe mode capable in game.cpp
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 

        // Use default shader
        shader->use();

        // Enable openGL color/alpha blending.
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void Renderer::Draw(Model* light, vector<Model*> scene) {
        // Check we have a light and models
        assert(light != nullptr && "ERROR: No light provided!");
        assert(scene.size() > 0 && "ERROR: Scene is empty!");

        // BG and clearing buffers
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Projection matrix
        float fov = glm::radians(camera->Zoom);
        float aspectRatio = (float)windowWidth / (float)windowHeight;

        glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), aspectRatio, 0.1f, 100.0f);

        // View matrix
        glm::mat4 view = camera->GetViewMatrix();

        // Uniforms
        int transformLoc = glGetUniformLocation(shader->ID, "transform");
        int modelViewLoc = glGetUniformLocation(shader->ID, "view");
        int modelViewPosLoc = glGetUniformLocation(shader->ID, "viewPos");
        int modelProjectionLoc = glGetUniformLocation(shader->ID, "projection");
        int boolLoc = glGetUniformLocation(shader->ID, "calculateLighting");
        int colorLoc = glGetUniformLocation(shader->ID, "color");

        // Update light translate, send to uniform
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(light->getTransform()));

        // Update light color, enable rendering calculations 
        glUniform3f(colorLoc, light->color.x, light->color.y, light->color.z);
        glUniform1i(boolLoc, 0);

        int lightPosLoc = glGetUniformLocation(shader->ID, "lightPos");
        glUniform3f(lightPosLoc, light->p.x, light->p.y, light->p.z);// Set light position.
        light->draw(*shader);

        // Render all other objects in the scene
        for (Model* model : scene) {
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model->getTransform()));
            glUniformMatrix4fv(modelViewLoc, 1, GL_FALSE, glm::value_ptr(view));
            glUniformMatrix4fv(modelProjectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

            // Send model data
            glUniform3f(colorLoc, model->color.x, model->color.y, model->color.z);
            glUniform3f(modelViewPosLoc, camera->Position.x, camera->Position.y, camera->Position.z);
            glUniform1i(boolLoc, 1);

            // Render model
            model->draw(*shader);
        }
    }
}