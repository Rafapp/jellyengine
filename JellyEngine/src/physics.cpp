#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include "physics.h"

PhysicsObject::PhysicsObject() : position(0.0f, 1.0f, 0.0f), velocity(0.0f), acceleration(0.0f), hasCollided(false) {
    // Constructor initializes position, velocity, and acceleration to zero
}

void PhysicsObject::update(float deltaTime) {
    // The ground plane is at y = -0.25
    float groundLevel = 0.0f;

    if (hasCollided) {
        velocity = glm::vec3(0.0f);
        return;
    }

    // Update the velocity based on acceleration
    velocity += acceleration * deltaTime;

    // Predict the next position
    glm::vec3 predictedPosition = position + velocity * deltaTime;

    // Calculate the lowest point of the AABB
    glm::vec3 lowestPoint = predictedPosition + aabbMin;

    // Check for collision with the ground
    if (lowestPoint.y <= groundLevel) {
        hasCollided = true; // Collision detected
        position.y = groundLevel - aabbMin.y; // Adjust to sit on ground
        velocity.y = 0.0f; // Stop downward movement
    }
    else {
        position = predictedPosition; // Update position as no collision occurred
    }
}

void PhysicsObject::setAABB(const glm::vec3& min, const glm::vec3& max) {
    aabbMin = min;
    aabbMax = max;
}