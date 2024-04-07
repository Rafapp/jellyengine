#include "spring.h"
#include "mesh.h"

Spring::Spring(unsigned int pA, unsigned int pB, float rest, float stiff, float damp)
    : pointA(pA), pointB(pB), restLength(rest), stiffness(stiff), damping(damp) {}

// Calculate the force exerted by this spring
glm::vec3 Spring::calculateForce(const std::vector<Vertex>& vertices) const {
    // Access the positions of the pointA and pointB using their indices
    const glm::vec3& positionA = vertices[pointA].position;
    const glm::vec3& positionB = vertices[pointB].position;

    // Compute the vector from pointA to pointB
    glm::vec3 springVector = positionB - positionA;

    // Calculate the displacement from the rest length
    float currentLength = glm::length(springVector);
    float displacement = currentLength - restLength;

    // Normalize the spring vector to get the direction
    glm::vec3 direction = glm::normalize(springVector);

    // Calculate the force using Hooke's law
    glm::vec3 force = -stiffness * displacement * direction;

    // Damping based on the relative velocity of the two points
    glm::vec3 relativeVelocity = vertices[pointB].velocity - vertices[pointA].velocity;
    force -= damping * relativeVelocity;

    return force;
}