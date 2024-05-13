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

class SoftBody;

class PointMass {
public:
	PointMass(Vertex* vert, SoftBody* body, float restitution, float mass, float stiffness, float damping);
	~PointMass();

	vector<Spring> springs;
	Vertex* vert; // Pointer to vert being integrated
	SoftBody* body;

	glm::vec3 velocity;
	glm::vec3 acceleration;
	glm::vec3 forces;

	float restitution;
	float mass;
	float stiffness;
	float damping;

	void AddSpring(Vertex* ref);
	void Integrate(float dt);
};

class SoftBody : public Model {
public:
	SoftBody(std::string path, float restitution, float mass, float stiffness, float damping);
	~SoftBody();

	float restitution;
	float mass;
	float stiffness;
	float damping;

	void AddForce(glm::vec3(force));
	void Update(float dt);
	void Reset();
	
	// Vertices we draw, initially set to model's verts
	vector<Vertex> dynamicVertices;
	vector<PointMass> massSpringSystem;
};