/*
 * PHYSICS: Class for soft and rigidbody physics objects
 */

#include <iostream>
#include <string>

#include "physics.h"

SoftBody::SoftBody(std::string path) : Model(path) {
	assert(meshes.size() > 0 && "ERROR: More than one mesh provided for softbody in this model!");
	pointMasses = vector<Vertex>(meshes[0].vertices);
}

void SoftBody::Update() {
	// Euler integrate here
	// -

	meshes[0].UpdateVertices(pointMasses);
}

void SoftBody::Reset() {

}

SoftBody::~SoftBody() {

}