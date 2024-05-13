/*
 * PHYSICS: Class for soft and rigidbody physics objects
 */

#include <iostream>
#include <string>

#include "physics.h"

/*
 * Soft body
 */
int springCount = 0;

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
	std::cout << "VERT COUNT: " << sizeof(dynamicVertices);
	std::cout << "SPRING COUNT: " << springCount << std::endl;
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
	this->damping = damping;

	velocity = glm::vec3(0.0);
	acceleration = glm::vec3(0.0);
	forces = glm::vec3(0.0);

	// Add springs based on nearby distance
	// TODO: Update this algorithm to something more reliable
	for (Vertex& v : body->dynamicVertices) {
		if (&v == vert) return;
		if (glm::distance(vert->position, v.position) < 100.0) {
			AddSpring(&v);
		}
	}
}

PointMass::~PointMass() {

}

void PointMass::AddSpring(Vertex* ref) {
	Spring s;
	s.neighbor = ref;
	s.restLength = glm::distance(vert->position, ref->position);
	springs.push_back(s);
	std::cout << "create spring from: " << std::endl;
	std::cout << vert->position.x << ", " << vert->position.y << ", " << vert->position.z << std::endl;
	std::cout << "to: " << std::endl;
	std::cout << ref->position.x << ", " << ref->position.y << ", " << ref->position.z << std::endl;
	std::cout << "spring distance: " << glm::distance(vert->position, ref->position) << std::endl;
	std::cout << std::endl;
	springCount++;
}

void PointMass::Integrate(float dt) {

	// TODO: Make floor collisions not hardcoded, add rigid->soft body collisions
	glm::mat4 transform = body->getTransform();
	glm::mat4 inverse = glm::inverse(transform);

	glm::vec3 world = transform * glm::vec4(vert->position, 1);

	if (world.y <= 0.0) {
		velocity = glm::vec4(velocity.x, -velocity.y * restitution, velocity.z, 1);
	} 

	// Calculate spring forces
	for (Spring s : springs) {
		// F = -kx
		forces += -stiffness * (vert->position - s.restLength);
	}

	acceleration = forces / mass;
	velocity += acceleration * dt;
	vert->position += velocity * dt;
	//velocity *= damping;
	forces = glm::vec3(0.0);
}