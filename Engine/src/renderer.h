/*
 * RENDERER: Singleton that handles OpenGL draw calls
 */

#pragma once

#include "camera.h"
#include "shader.h"
#include "model.h"

namespace Renderer {
	static Camera* camera;
	static Shader* shader;
	static Model* model;
	static Model* light;
	static Model* plane;

	static void Setup();
	static void Draw();
}