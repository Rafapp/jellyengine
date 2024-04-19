#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include "physics.h"

// This class handles rigid body physics for a single object
PhysicsObject::PhysicsObject() : 
    position(0.0f, 1.0f, 0.0f), 
    velocity(0.0f), 
    acceleration(0.0f), 
    restitution(0.8f),
    velocityThreshold(0.1f),
    hasCollided(false) { }

void PhysicsObject::update(float deltaTime, glm::vec3 scaledAABBMin) {
    // Current removed for simplicity
}

void PhysicsObject::setAABB(const glm::vec3& min, const glm::vec3& max) {
    aabbMin = min;
    aabbMax = max;
}