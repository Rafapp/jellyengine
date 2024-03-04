#pragma once

#include <vector>
#include <String>

#include <glm/glm.hpp>

#include "shader.h"

using namespace std;

struct Vertex {
	glm::vec3 position; // Position vector
	glm::vec3 color; // Color vector
	glm::vec3 normal; // Normal vector
	glm::vec3 texCoords; // Texture coordinates
};

struct Texture {
	unsigned int id; // Texture ID
	string type; // Texture type
};

class Mesh {
public:
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;

	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);

	void draw(Shader& shader);
private:
	unsigned int VAO, VBO, EBO; // Vertex Array Object, Vertex Buffer Object, Element Buffer Object
	void setup();
};
