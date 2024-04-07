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
	// Rendering attributes
	glm::vec3 position; // Position vector
	glm::vec3 color;	// Color vector
	glm::vec3 normal;	// Normal vector
	glm::vec3 texCoords; // Texture coordinates

	// Physics properties
	glm::vec3 velocity;  // Current velocity
	glm::vec3 force;     // Accumulated force
	float mass;          // Mass of the vertex
	float restitution;   // Coefficient of restitution for collisions
	float damping;       // Damping factor to reduce velocity over time
	bool fixed;          // Indicates if the vertex is fixed in space
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

	// Constructor should initialize physics properties of vertices
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);

	void setup();
	void draw(Shader& shader);
	void updateSoftBodyPhysics(float deltaTime);

	unsigned int VAO, VBO, EBO; // Vertex Array Object, Vertex Buffer Object, Element Buffer Object
};
