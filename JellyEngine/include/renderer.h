#pragma once

/*
 * RENDERER: Takes care of OpenGL rendering backend
 */

#include <camera.h>
#include <shader.h>
#include <model.h>

using namespace std;

class Renderer {
public:
	void setup(float wWidth, float wHeight);
	void draw(float wWidth, float wHeight);

	Camera* camera;
	Shader* mainShader;

	glm::vec3 lightPos; // TODO: Abstract to light class
	glm::mat4 modelTransform; // TODO: Abstract to mesh class
	glm::mat4 lightTransform; // TODO: Abstract to mesh class
	unsigned int VAO; // TODO: This has to go, classes need to be abstracted, but we can test with it for now

	Model* model;
	Model* light;

	glm::vec3 modelColor = glm::vec3(0.0, 1.0, 1.0);
	glm::vec3 lightColor = glm::vec3(1.0, 1.0, 1.0);
};