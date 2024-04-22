/*
 * GAME OBJECT: Stores position, rotation and scale data
 */

#include<glm/gtc/type_ptr.hpp>

#include "gameObject.h"

glm::mat4 GameObject::getTransform() {
	glm::mat4 I = glm::mat4(1.0f);
	glm::mat4 T = glm::translate(I, p);
	glm::mat4 Rx = glm::rotate(I, glm::radians(r.x), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 Ry = glm::rotate(I, glm::radians(r.y), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 Rz = glm::rotate(I, glm::radians(r.z), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 S = glm::scale(I, s);
	return T * Rz * Ry * Rx * S; // TODO: Rotation order support
}