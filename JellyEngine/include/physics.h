#pragma once

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// A simple structure to represent a Vertex with position and color properties
struct Vertex {
    glm::vec3 position;
    glm::vec3 color;

    Vertex(const glm::vec3& pos, const glm::vec3& col) 
        : position(pos), color(col) {}
};

// Handles the collection of vertices and the object's physics properties
struct PhysicsObject {
    std::vector<Vertex> vertices;
    glm::vec3 velocity;
    glm::vec3 force;
    float mass;
    float damping;      // A coefficient for simulating air resistance
    float restitution; // A coefficient for the bounce effect
    float friction;    // A coefficient for simulating friction

    PhysicsObject(const std::vector<Vertex>& verts, float m, float d, float r, float pY, float f);
    void applyForce(const glm::vec3& newForce);
    glm::vec3 calculateCenter() const;
    void applyGravity();
    void scaleHeight(float scaleFactor);
    void integrate(float dt);

};