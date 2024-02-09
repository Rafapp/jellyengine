#pragma once

/*
 * RENDERER: Takes care of OpenGL rendering backend
 */

#include "camera.h"
#include "shader.h"
#include "model.h"

using namespace std;

class Renderer {
public:
	void setup(float wWidth, float wHeight);
	void draw(float wWidth, float wHeight);

	Camera* camera;
	Shader* mainShader;

	Model* model;
	Model* light;
};