#pragma once

#include <glm/glm.hpp>

class Spring {
public:
    unsigned int pointA;  // Pointer to the position of the first mass point
    unsigned int pointB;  // Pointer to the position of the second mass point
    float restLength;   // The length at which the spring is at rest
    float stiffness;    // Spring constant (k)

    Spring(unsigned int pA, unsigned int pB, float rest, float k)
        : pointA(pA), pointB(pB), restLength(rest), stiffness(k) {}
};