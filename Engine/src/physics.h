/*
 * PHYSICS: Class for soft and rigidbody physics objects
 */

#pragma once

#include <vector>
#include <string>

#include <glm/glm.hpp>

#include "model.h"

class SoftBody : public Model{
public:
	SoftBody(std::string path);
	~SoftBody();

	void Update();
	void Reset();

	// We update these vertices (copy), not the ones of the original mesh,
	// and pass them as a vertex buffer for rendering.
	vector<Vertex> pointMasses; 
};