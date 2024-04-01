#pragma once

/*
 * RENDERER: Takes care of OpenGL rendering backend
 */

#include "camera.h"
#include "shader.h"
#include "model.h"
#include <chrono> // add timer variables

using namespace std;

class Renderer {
public:
	void setup(float wWidth, float wHeight);
	void draw(float wWidth, float wHeight);

	Camera* camera;
	Shader* mainShader;

	Model* model;
	Model* light;
	Model* plane;

	// Timer variables
	void logRenderTime(const std::string& objectName);
	std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
	std::chrono::time_point<std::chrono::high_resolution_clock> endTime;
	bool modelRenderedOnce = false;

	// Frame Rate
	void calculateAndDisplayFPS();
	std::chrono::high_resolution_clock::time_point lastFrameTime;
	std::chrono::high_resolution_clock::time_point lastFPSUpdateTime;
	int frameCount = 0;
	int totalFrameCount = 0;  // Total frames counted in the current minute
};