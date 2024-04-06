#pragma once

#include <glm/glm.hpp>

class Spring {
public:
    glm::vec3* pointA;  // Pointer to the position of the first mass point
    glm::vec3* pointB;  // Pointer to the position of the second mass point
    float restLength;   // The length at which the spring is at rest
    float stiffness;    // Spring constant (k)

    Spring(glm::vec3* pA, glm::vec3* pB, float rest, float k)
        : pointA(pA), pointB(pB), restLength(rest), stiffness(k) {}

    // Function to calculate the force exerted by the spring
    glm::vec3 calculateForce() {
        // Vector from point A to point B
        glm::vec3 springVector = *pointB - *pointA;
        // Calculate the displacement from the rest length
        float displacement = glm::length(springVector) - restLength;
        // Normalize the spring vector
        glm::vec3 direction = glm::normalize(springVector);
        // Hooke's Law: F = -kx
        glm::vec3 force = -stiffness * displacement * direction;
        return force;
    }
};