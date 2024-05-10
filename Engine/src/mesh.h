/*
 * MESH: Stores vertex, normal, and texture data for SINGLE mesh and draw it.
 */

#pragma once

#include <vector>
#include <String>

#include <glm/glm.hpp>

#include "shader.h"

using namespace std;

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 texCoords;
};

struct Texture {
	unsigned int id;
	string type;
};

class Mesh {
public:
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;

	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);

	void draw(Shader& shader);
	void UpdateVertices(vector<Vertex> vertices);

private:
	unsigned int VAO, VBO, EBO;
	void setup();
};