#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include "physics.h"

PhysicsObject::PhysicsObject() : 
    position(0.0f, 1.0f, 0.0f), 
    velocity(0.0f), 
    acceleration(0.0f), 
    restitution(0.8f),
    velocityThreshold(0.1f),
    hasCollided(false) { }

void PhysicsObject::update(float deltaTime, glm::vec3 scaledAABBMin) {
    velocity += acceleration * deltaTime;
    glm::vec3 nextPosition = position + velocity * deltaTime;

    if ((nextPosition.y + scaledAABBMin.y) <= ground) {
        if (!hasCollided) {  // Only apply restitution on the first collision
            velocity.y = -velocity.y * restitution;
            hasCollided = true;
        }
        position.y = ground - scaledAABBMin.y;  // Adjust position to sit on the ground
    }
    else {
        hasCollided = false;
        position = nextPosition;
    }

    // Apply a damping effect to gradually reduce the bounce over time
    if (hasCollided && std::abs(velocity.y) < velocityThreshold) {
        velocity.y = 0;
        acceleration = glm::vec3(0);
    }
}

void PhysicsObject::setAABB(const glm::vec3& min, const glm::vec3& max) {
    aabbMin = min;
    aabbMax = max;
}