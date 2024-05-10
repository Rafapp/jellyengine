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
	assert(meshes.size() > 0 && "ERROR: More than one mesh provided for softbody in this model!");
	dynamicVertices = vector<Vertex>(meshes[0].vertices);
}

SoftBody::~SoftBody() {

}

void SoftBody::CreateMassSpringSystem() {
	
}

void SoftBody::Update(float dt) {
	// Euler integrate here
	// -

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
}

void PointMass::AddNeighbor(Vertex* ref) {
	Spring s;
	s.neighbor = ref;
	s.restLength = glm::distance(vert->position, ref->position);
}

void PointMass::Integrate() {

}