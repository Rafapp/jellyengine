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

	glm::mat4 translate;
	unsigned int VAO; // TODO: This has to go, classes need to be abstracted, but we can test with it for now

	Model* model;
};