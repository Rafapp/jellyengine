#include <glm/glm.hpp>
#include <iostream>
#include <vector>

using namespace std;

// A simple structure to represent a Vertex with only position and color properties
struct Vertex {
    glm::vec3 position;
    glm::vec3 color;

    Vertex(const glm::vec3& pos, const glm::vec3& col)
        : position(pos), color(col) {}
};

// Handles the collection of vertices, the object's velocity, and its physics integration
struct Object {
    std::vector<Vertex> vertices;
    glm::vec3 velocity;
    glm::vec3 force;
    float mass;
    float damping;

    Object(const std::vector<Vertex>& verts, float m, float d)
        : vertices(verts), velocity(glm::vec3(1.0f)), force(glm::vec3(0)), mass(m), damping(d) {}

    glm::vec3 calculateCenter() const {
        glm::vec3 center(0.0f);
        for (const auto& v : vertices) {
            center += v.position;
        }
        center /= vertices.size();
        return center;
    }

    void applyForce(const glm::vec3& newForce) {
        force += newForce;
    }

    void integrate(float dt) {
        // Apply damping to the velocity
        velocity *= damping;

        // Update velocity based on force and mass
        glm::vec3 acceleration = force / mass;
        velocity += acceleration * dt;

        // Calculate new position based on velocity
        glm::vec3 center = calculateCenter();
        glm::vec3 newCenter = center + velocity * dt;

        // Collision detection and response
        if (newCenter.x <= -1.0f || newCenter.x >= 1.0f) {
            velocity.x *= -1;
            newCenter = center;
        }
        if (newCenter.y <= -1.0f || newCenter.y >= 1.0f) {
            velocity.y *= -1;
            newCenter = center;
        }

        // Update vertex positions relative to the new center
        glm::vec3 displacement = newCenter - center;
        for (auto& v : vertices) {
            v.position += displacement;
        }

        // Reset force after each integration step
        force = glm::vec3(0);
    }
};

// Define each vertex only once
std::vector<Vertex> cubeVertices = {
    // positions        // texture coords
   Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f)), // 0
   Vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f)), // 1
   Vertex(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f)), // 2
   Vertex(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 0.0f)), // 3
   Vertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 1.0f)), // 4
   Vertex(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 1.0f)), // 5
   Vertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.0f, 0.0f)), // 6
   Vertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.5f, 0.0f))  // 7
};

// Define indices for each triangle of the cube
unsigned int cubeIndices[] = {
    // Back face
    0, 1, 2,
    2, 3, 0,
    // Front face
    4, 5, 6,
    6, 7, 4,
    // Left face
    0, 4, 7,
    7, 3, 0,
    // Right face
    1, 5, 6,
    6, 2, 1,
    // Bottom face
    0, 1, 5,
    5, 4, 0,
    // Top face
    3, 2, 6,
    6, 7, 3
};