#pragma once

#include <vector>
#include <String>
#include <set>
#include <utility> // For std::pair
#include <algorithm> // For std::minmax

#include <glm/glm.hpp>

#include "shader.h"
#include "spring.h"

using namespace std;

struct Vertex {
	glm::vec3 position; // Position vector
	glm::vec3 color; // Color vector
	glm::vec3 normal; // Normal vector
	glm::vec3 texCoords; // Texture coordinates

	// New physics properties for mass point representation
	glm::vec3 velocity;
	glm::vec3 force;
	float restitution;
	float mass;
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
	vector<Spring> springs;

	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);

	void draw(Shader& shader);
	void applyPhysics(float deltaTime); // Apply physics for vertices
	void initSpringsFromAssimpData(const std::vector<aiMesh*>& aiMeshes); // Initialize springs from Assimp data

private:
	unsigned int VAO, VBO, EBO; // Vertex Array Object, Vertex Buffer Object, Element Buffer Object
	void setup();
};
