/*
 * GAME OBJECT: Stores position, rotation and scale data
 */

#pragma once

#include <glm/glm.hpp>

class GameObject {
public:
	GameObject() {
		p = glm::vec3(0.0f);
		r = glm::vec3(0.0f);
		s = glm::vec3(1.0f);
	}
	~GameObject() {}

	glm::vec3 p;
	glm::vec3 r;
	glm::vec3 s;

	glm::mat4 getTransform();
private:
};