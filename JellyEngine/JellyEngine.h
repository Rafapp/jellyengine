#pragma once

#include <GLFW/glfw3.h>

#include "renderer.h"
#include "shader.h"
#include "camera.h"

int setup();
void update();
void shutdownEngine();  // Renamed from 'exit' to 'shutdownEngine'