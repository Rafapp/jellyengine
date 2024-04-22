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

	void Setup();
	void Draw(Model* light, vector<Model*> scene);
}