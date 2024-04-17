#include "spring.h"
#include "mesh.h"

Spring::Spring(unsigned int pA, unsigned int pB, float rest, float stiff, float damp)
    : pointA(pA), pointB(pB), restLength(rest), stiffness(stiff), damping(damp) {}

// Calculate the force exerted by this spring
glm::vec3 Spring::calculateForce(const glm::vec3& positionA, const glm::vec3& positionB) const {
    glm::vec3 springVector = positionB - positionA;
    float currentLength = glm::length(springVector);
    glm::vec3 force = glm::vec3(0.0f);

    if (currentLength != 0) {
        glm::vec3 direction = glm::normalize(springVector);
        float displacement = currentLength - restLength;
        force = -stiffness * displacement * direction;
    }

    return force;
}