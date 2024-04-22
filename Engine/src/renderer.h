/*
 * RENDERER: Singleton that handles OpenGL draw calls
 */

#pragma once

#include "camera.h"
#include "shader.h"
#include "model.h"

namespace Renderer {
	extern Camera* camera;
	extern Shader* shader;
	extern Model* model;
	extern Model* light;
	extern Model* plane;

	void Setup();
	void Draw();
}