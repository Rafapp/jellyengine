#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include "physics.h"

using namespace std;

// A simple structure to represent a Vertex with only position and color properties
struct Vertex {
    glm::vec3 position;
    glm::vec3 color;

    Vertex(const glm::vec3& pos, const glm::vec3& col)
        : position(pos), color(col) {}
};

// Handles the collection of vertices, the object's velocity, and its physics integration
class PhysicsObject {
    std::vector<Vertex> vertices;
    glm::vec3 velocity;
    glm::vec3 force;
    glm::vec3 gravity;
    float mass;
    float damping;

    PhysicsObject(const std::vector<Vertex>& verts, float m, float d, glm::vec3 g)
        : vertices(verts), velocity(glm::vec3(0.0f)), force(glm::vec3(0)), mass(m), damping(d), gravity(g) {}

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

    void applyGravity() {
        for (auto& vertex : vertices) {
            applyForce(gravity * mass);
        }
	}

    void scaleHeight(float scaleFactor) {
        for (auto& vertex : vertices) {
			vertex.position.y *= scaleFactor;
		}
	}

    void integrate(float dt) {
        velocity *= damping;

        // Update velocity based on force and mass
        glm::vec3 acceleration = force / mass;
        velocity += acceleration * dt;

        // Calculate new position based on velocity
        glm::vec3 center = calculateCenter();
        glm::vec3 newCenter = center + velocity * dt;

        // Update vertex positions and check for collisions individually
        for (auto& v : vertices) {
            // Integrate velocity to get new position
            v.position += velocity * dt;

            // Collision detection with the ground plane at y = 0
            if (v.position.y < 0.0f) {
                v.position += velocity * dt;
                // Check for collision with the ground
                if (v.position.y < 0.0f) {
                    v.position.y = 0.0f;
                    velocity.y = -velocity.y * 0.9f;  // Apply some restitution
                    velocity.x *= 0.9f;  // Simulate friction by reducing x velocity
                    velocity.z *= 0.9f;  // Simulate friction by reducing z velocity
                }
            }

            cout << "newCenter: " << newCenter.x << " " << newCenter.y << " " << newCenter.z << endl;
        }

        // Reset force after each integration step
        force = glm::vec3(0);
    }
};