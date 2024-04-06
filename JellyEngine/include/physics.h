#pragma once

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class PhysicsObject {
public:
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;
    float restitution; // Bounce restitution coefficient
    float velocityThreshold; // Velocity below which the object will stop bouncing
    float ground = -0.25;

    glm::vec3 aabbMin; // Minimum corner of the AABB
    glm::vec3 aabbMax; // Maximum corner of the AABB
    bool hasCollided = false;

    PhysicsObject();
    void update(float deltaTime, glm::vec3 scaledAABBMin);
    void setAABB(const glm::vec3& min, const glm::vec3& max);
};
