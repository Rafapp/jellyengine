﻿#pragma once

// Core Libraries
#include <GLFW/glfw3.h>
#include <vector>

// Engine Components
#include "renderer.h"
#include "shader.h"
#include "camera.h"
#include "model.h"
#include "physics.h"

// Engine Core
int setup(); // Engine setup
void update(); // Engine update (called per frame)
void shutdownEngine(); // Cleanup and shutdown engine

// Callback Functions
void framebuffer_size_callback(GLFWwindow* window, int width, int height); // Window resize callback
void mouse_callback(GLFWwindow* window, double xpos, double ypos); // Mouse movement callback
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset); // Scroll callback
void processInput(GLFWwindow* window); // Input processing
static void error_callback(int error, const char* description); // Error callback

// Utility Functions
std::vector<Vertex> modelToVertices(Model& model); // Convert model data to vertices

// Main
int main(); // Main function