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
	for (auto a : pointMasses) {
		std::cout << a.position.x << "," << a.position.y << "," << a.position.z << std::endl;
	}
}

void SoftBody::Reset() {

}

SoftBody::~SoftBody() {

}