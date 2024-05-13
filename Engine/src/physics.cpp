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
	
	// Set members
	this->restitution = restitution;
	this->mass = mass;
	this->stiffness = stiffness;
	this->damping = damping;
	
	// Create copy of mesh's initial vertices
	dynamicVertices = vector<Vertex>(meshes[0].vertices);

	// Create mass spring system using dynamic vertices
	for (Vertex& v : dynamicVertices) {
		PointMass p(&v, this, restitution, mass, stiffness, damping);
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
	// Reset soft body to original state (original position included)
	dynamicVertices = vector<Vertex>(meshes[0].vertices);
	for (PointMass& p : massSpringSystem) {
		p.velocity = glm::vec3(0.0);
		p.acceleration = glm::vec3(0.0);
		p.forces = glm::vec3(0.0);
	}
}

/*
 * Point mass
 */
PointMass::PointMass(Vertex* vert, SoftBody* body, float restitution, float mass, float stiffness, float damping){
	this->vert = vert; // Reference vertex in dynamic vertices
	this->body = body;

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
	glm::mat4 inverse = glm::inverse(body->getTransform());
	glm::vec4 world = inverse * glm::vec4(vert->position, 1);
	std::cout << "world space: " << world.x << ", " << world.y << ", " << world.z << ", " << std::endl;

	if (world.y <= -10.0) {
		velocity = glm::vec3(velocity.x, -velocity.y * restitution, velocity.z);
	} 

	acceleration = forces / mass;
	velocity += acceleration * dt;
	vert->position += velocity * dt;
	//velocity *= damping;
	forces = glm::vec3(0.0);
}