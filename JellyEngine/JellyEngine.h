#pragma once

#include <renderer.h>
#include <GLFW/glfw3.h>

Renderer renderer;
GLFWwindow* window; // TODO: Same

int setup();
void update();
void exit();

