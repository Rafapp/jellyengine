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
    float damping;
    float restitution; // A coefficient for the bounce effect
    float planeY;       // The y-position of the plane for collision detection
    float friction;    // A coefficient for simulating friction

    PhysicsObject(const std::vector<Vertex>& verts, float m, float d, float r, float pY, float f)
        : vertices(verts), velocity(glm::vec3(0.0f)), force(glm::vec3(0)), mass(m), damping(d), restitution(r), planeY(pY), friction(f) {}

    void applyForce(const glm::vec3& newForce) {
        force += newForce;
    }

    void collideWithPlane(float dt) {
        bool collisionDetected = false;

        for (auto& v : vertices) {
            if (v.position.y <= planeY) {
                // Correct the vertex position to be just on the plane
                v.position.y = planeY;

                // Indicate that a collision has been detected
                collisionDetected = true;
            }
        }

        // Apply collision response if a collision is detected
        if (collisionDetected && velocity.y < 0) {
            // Reflect the velocity in the Y direction and apply restitution
            velocity.y = -velocity.y * restitution;

            // Apply friction to the horizontal components of the velocity
            velocity.x *= (1 - friction);
            velocity.z *= (1 - friction);
        }
    }

    void integrate(float dt) {
        glm::vec3 acceleration = force / mass;
        glm::vec3 newVelocity = velocity + acceleration * dt;
        glm::vec3 newPosition;

        for (auto& v : vertices) {
            // Predict the new position
            newPosition = v.position + newVelocity * dt;

            // Check for collision during the movement
            if (newPosition.y <= planeY) {
                // Calculate the time of collision
                float t = (planeY - v.position.y) / newVelocity.y;

                // Correct the position to the collision point
                newPosition = v.position + newVelocity * t;

                // Reflect the velocity component in the Y direction and apply restitution
                newVelocity.y = -newVelocity.y * restitution;

                // Apply friction to the X and Z axes if desired
                newVelocity.x *= (1 - friction);
                newVelocity.z *= (1 - friction);

                // Since we had a collision, set the vertex position to the collision point
                v.position = newPosition;

                // Update the velocity of the object
                velocity = newVelocity;

                // Break after the collision is handled for this vertex
                break;
            }
        }

        // If no collision, update positions normally
        if (!isCollidingWithPlane()) {
            for (auto& v : vertices) {
                v.position += newVelocity * dt;
            }
        }

        // Apply damping to the velocity
        velocity *= damping;

        // Reset force after each integration step
        force = glm::vec3(0);
    }

    bool isCollidingWithPlane() {
        for (auto& v : vertices) {
            if (v.position.y <= planeY) {
                return true;
            }
        }
        return false;
    }

};