/*
 * PHYSICS: Class for soft and rigidbody physics objects
 */

#include <iostream>
#include <string>

#include "physics.h"

/*
 * Soft body
 */
SoftBody::SoftBody(std::string path) : Model(path) {
	assert(meshes.size() > 0 && "ERROR: More than one mesh provided for softbody in this model, provide a single mesh!");

	// Create copy of mesh's initial vertices
	dynamicVertices = vector<Vertex>(meshes[0].vertices);

	// Create mass spring system using dynamic vertices
	for (Vertex& v : dynamicVertices) {
		PointMass p(&v, this->stiffness, this->damping);
		massSpringSystem.push_back(p);
	}
}

SoftBody::~SoftBody() {
	
}

void SoftBody::AddForce(glm::vec3(force)) {
	for (PointMass& p : massSpringSystem) {
		p.forces += force;
	}
}

void SoftBody::Update(float dt) {
	// Integrate vertices in mass spring system
	for (PointMass &p : massSpringSystem) {
		p.forces +=  glm::vec3(0.0, -10, 0.0);
		p.Integrate(dt);
	}
	// Update vertices for rendering
	meshes[0].UpdateVertices(dynamicVertices);
}

void SoftBody::Reset() {

}

/*
 * Point mass
 */
PointMass::PointMass(Vertex* ref, float stiffness, float damping) {
	vert = ref;

	this->stiffness = stiffness;
	this->damping = stiffness;

	mass = 1.0;
	velocity = glm::vec3(0.0);
	acceleration = glm::vec3(0.0);
	forces = glm::vec3(0.0);
}

PointMass::~PointMass() {

}

void PointMass::AddNeighbor(Vertex* ref) {
	Spring s;
	s.neighbor = ref;
	s.restLength = glm::distance(vert->position, ref->position);
}

void PointMass::Integrate(float dt) {
	acceleration = forces / mass;
	velocity += acceleration * dt;
	vert->position += velocity * dt;
	forces = glm::vec3(0.0);
}