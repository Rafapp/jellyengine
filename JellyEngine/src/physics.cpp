#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include "physics.h"

PhysicsObject::PhysicsObject() : position(0.0f), velocity(0.0f), acceleration(0.0f) {
    // Constructor initializes position, velocity, and acceleration to zero
}

void PhysicsObject::update(float deltaTime) {
    // Update the velocity based on acceleration
    velocity += acceleration * deltaTime;
    // Update the position based on velocity
    position += velocity * deltaTime;
    
    // Print the position of the object
    std::cout << "Position: " << position.x << ", " << position.y << ", " << position.z << std::endl;
}