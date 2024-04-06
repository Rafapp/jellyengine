/*
 * MESH: Load and draw single/multiple meshes
 */

#include <glad/glad.h>
#include <assimp/scene.h>
#include <iostream>
#include "mesh.h"


using namespace std;

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    setup();
}

void Mesh::setup() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
        &indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    // vertex texture coords
    //glEnableVertexAttribArray(2);
    //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);
}

void Mesh::draw(Shader& shader) {
    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::applyPhysics(float deltaTime) {
    // Reset forces for each vertex to zero
    for (Vertex& vertex : vertices) {
        vertex.force = glm::vec3(0.0f);
    }

    // Apply forces from all springs to connected vertices
    for (Spring& spring : springs) {
        // Access the positions using the indices
        glm::vec3& pointA = vertices[spring.pointA].position;
        glm::vec3& pointB = vertices[spring.pointB].position;

        // Calculate the force exerted by the spring
        glm::vec3 springVector = pointB - pointA;
        float displacement = glm::length(springVector) - spring.restLength;
        glm::vec3 direction = glm::normalize(springVector);
        glm::vec3 force = -spring.stiffness * displacement * direction;

        // Apply force to connected vertices
        vertices[spring.pointA].force += force;  // Apply to point A
        vertices[spring.pointB].force -= force;  // Apply to point B (opposite direction)
    }

    // Assume gravity and other forces have already been applied to the vertices
    for (Vertex& vertex : vertices) {
        // Integrate forces to update velocity
        glm::vec3 acceleration = vertex.force / vertex.mass;
        vertex.velocity += acceleration * deltaTime;

        // Integrate velocity to update position
        vertex.position += vertex.velocity * deltaTime;

        // Collision response with the floor
        if (vertex.position.y < -0.25f) {
            vertex.position.y = -0.25f;  // Correct the position to be on the floor

            // Reflect the velocity and apply restitution
            // Assuming restitution is defined for vertices; otherwise, use a global restitution value
            vertex.velocity.y *= -1.0f * vertex.restitution;

            // Optionally, apply some damping to the velocity to simulate energy loss upon collision
            vertex.velocity *= 0.9f;  // Adjust the damping factor as needed
        }

        // Reset force for the next iteration
        vertex.force = glm::vec3(0.0f);
    }
}

void Mesh::initSpringsFromAssimpData(const std::vector<aiMesh*>& aiMeshes) {
    std::set<std::pair<unsigned int, unsigned int>> uniqueEdgeSet;

    for (const auto* aiMesh : aiMeshes) {
        for (unsigned int i = 0; i < aiMesh->mNumFaces; i++) {
            const auto& face = aiMesh->mFaces[i];

            for (unsigned int j = 0; j < face.mNumIndices; j++) {
                unsigned int indexA = face.mIndices[j];
                unsigned int indexB = face.mIndices[(j + 1) % face.mNumIndices]; // Wrap to form edges

                // Create a unique identifier for the edge
                auto edge = std::minmax(indexA, indexB);

                // Check if the edge is already added
                if (!uniqueEdgeSet.count(edge)) {
                    uniqueEdgeSet.insert(edge);

                    // Calculate the rest length of the spring based on the initial positions
                    float restLength = glm::distance(vertices[indexA].position, vertices[indexB].position);

                    // Assuming stiffness is a predefined constant or configurable parameter
                    float stiffness = 1.0f; // Placeholder value, adjust as needed

                    // Add the new Spring to the Mesh
                    springs.push_back(Spring(indexA, indexB, restLength, stiffness));
                }
            }
        }
    }
}