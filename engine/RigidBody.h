//
// Created by Andrew Graser on 9/6/2023.
//

#ifndef PHYSICS_ENGINE_RIGIDBODY_H
#define PHYSICS_ENGINE_RIGIDBODY_H

#include <glm/glm.hpp>

struct RigidBody {
    glm::vec2 position = {0.0f, 0.0f};
    glm::vec2 linearVelocity = {0.0f, 0.0f};
    glm::vec2 linearAcceleration = {0.0f, 0.0f};
    float angle = 0.0f;
    float angularVelocity = 0.0f;
    glm::vec2 force = {0.0f, 0.0f};
    float torque = 0.0f;
    bool hasGravity = true;
};

#endif //PHYSICS_ENGINE_RIGIDBODY_H
