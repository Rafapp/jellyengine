#pragma once

#include <glm/glm.hpp>
#include <vector>

struct Vertex; // Forward declaration to avoid circular dependencies

class Spring {
public:
    unsigned int pointA, pointB;  // Indices of the connected vertices
    float restLength;   // The length at which the spring is at rest
    float stiffness;    // Spring constant (k)
    float damping;	  // Damping factor to avoid oscillations 

    Spring(unsigned int pA, unsigned int pB, float rest, float stiff, float damp);

    // Calculate the force exerted by this spring
    glm::vec3 calculateForce(const std::vector<Vertex>& vertices) const;
};