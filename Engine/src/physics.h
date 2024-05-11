/*
 * PHYSICS: Class for soft and rigidbody physics objects
 */

#pragma once

#include <vector>
#include <string>

#include <glm/glm.hpp>

#include "model.h"
#include "mesh.h"

struct Spring {
	Vertex* neighbor;
	float restLength;
};

class PointMass {
public:
	PointMass(Vertex* ref, float stiffness, float damping);
	~PointMass();

	vector<Spring> springs;
	Vertex* vert; // Pointer to vert being integrated

	glm::vec3 velocity;
	glm::vec3 acceleration;
	glm::vec3 forces;

	float mass;
	float stiffness;
	float damping;

	void AddNeighbor(Vertex* ref);
	void Integrate(float dt);
};

class SoftBody : public Model{
public:
	SoftBody(std::string path);
	~SoftBody();

	float stiffness;
	float damping;

	void AddForce(glm::vec3(force));
	void Update(float dt);
	void Reset();

private:	
	// Vertices we draw, initially set to model's verts
	vector<Vertex> dynamicVertices; 
	vector<PointMass> massSpringSystem;
};