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

    /*
    * Axis-Aligned Bounding Box (AABB) for collision detection
    * Uses a bounding volume that encapsulates your object
    */
    glm::vec3 aabbMin; // Minimum corner of the AABB
    glm::vec3 aabbMax; // Maximum corner of the AABB

    bool hasCollided;

    PhysicsObject();
    void update(float deltaTime);
    void setAABB(const glm::vec3& min, const glm::vec3& max);
};
