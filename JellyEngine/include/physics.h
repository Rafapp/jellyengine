#pragma once

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class PhysicsObject {
public:
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;

    PhysicsObject();
    void update(float deltaTime);
};
