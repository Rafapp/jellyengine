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
    if (!manualControlIsActive) {
        // glm::vec3 nextPosition = position + velocity * deltaTime;

        // Check collision with the ground
        //if ((nextPosition.y + scaledAABBMin.y) <= ground) {
            // position.y = ground - scaledAABBMin.y; // Adjust position to ground level
            // hasCollided = true; // Mark as collided
        // }
        // else {
            // position = nextPosition; // Update position if no collision
            // hasCollided = false;
        // }
    }
    // Reset manual control flag for next frame
    manualControlIsActive = false;
}

void PhysicsObject::setAABB(const glm::vec3& min, const glm::vec3& max) {
    aabbMin = min;
    aabbMax = max;
}