/*
 * GAME OBJECT: Stores position, rotation and scale data
 */

#include<glm/gtc/type_ptr.hpp>

#include "gameObject.h"

glm::mat4 GameObject::getTransform() {
	glm::mat4 I = glm::mat4(1.0f);
	glm::mat4 T = glm::translate(I, p);
	glm::mat4 S = glm::scale(I, s);
	return T * S; // TODO: Add rotation
}