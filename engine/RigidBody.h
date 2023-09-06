//
// Created by Andrew Graser on 9/6/2023.
//

#ifndef PHYSICS_ENGINE_RIGIDBODY_H
#define PHYSICS_ENGINE_RIGIDBODY_H

#include <glm/vec2.hpp>
#include "BoxParticle.h"

struct RigidBody{
    glm::vec2 position;
    glm::vec2 linearVelocity;
    float angle;
    float angularVelocity;
    glm::vec2 force;
    float torque;
    BoxParticle shape;
};

#endif //PHYSICS_ENGINE_RIGIDBODY_H
