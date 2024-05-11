/*
 * PHYSICS: Class for soft and rigidbody physics objects
 */

#include <iostream>
#include <string>

#include "physics.h"

/*
 * Soft body
 */
SoftBody::SoftBody(std::string path, float restitution, float mass, float stiffness, float damping) : Model(path) {
	assert(meshes.size() > 0 && "ERROR: More than one mesh provided for softbody in this model, provide a single mesh!");

	// Create copy of mesh's initial vertices
	dynamicVertices = vector<Vertex>(meshes[0].vertices);

	// Create mass spring system using dynamic vertices
	for (Vertex& v : dynamicVertices) {
		PointMass p(&v,this->restitution, this->mass, this->stiffness, this->damping);
		massSpringSystem.push_back(p);
	}
}

SoftBody::~SoftBody() {
	
}

void SoftBody::AddForce(glm::vec3(force)) {
	for (PointMass &p : massSpringSystem) {
		p.forces += force;
	}
}

void SoftBody::Update(float dt) {
	// Integrate vertices in mass spring system
	for (PointMass &p : massSpringSystem) {
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
PointMass::PointMass(Vertex* ref, float restitution, float mass, float stiffness, float damping){
	vert = ref; // Reference vertex in dynamic vertices

	this->restitution = restitution;
	this->mass = mass;
	this->stiffness = stiffness;
	this->damping = stiffness;

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
	// TODO: Make floor collisions not hardcoded, add rigid->soft body collisions
	if (vert->position.y <= -1.0) {
		vert->position.y = -1.0;
		velocity = glm::vec3(velocity.x, velocity.y * restitution, velocity.z);
	}
	acceleration = forces / mass;
	velocity += acceleration * dt;
	vert->position += velocity * dt;
	//velocity *= damping;
	forces = glm::vec3(0.0);
}