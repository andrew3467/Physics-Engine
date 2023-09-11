//
// Created by Andrew Graser on 9/6/2023.
//

#ifndef PHYSICS_ENGINE_RIGIDBODY_H
#define PHYSICS_ENGINE_RIGIDBODY_H

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include "AABB.h"



class RigidBody {
private:
public:
    float mass = 1.0f;
    glm::vec2 position = {0.0f, 0.0f};
    glm::vec2 velocity = {0.0f, 0.0f};
    glm::vec2 acceleration = {0.0f, 0.0f};
    glm::vec2 rotation = {0.0f, 0.0f};
    glm::vec2 force = {0.0f, 0.0f};
    bool hasGravity = true;

    glm::vec2 size;

    AABB aabb;

public:
    glm::mat4 model;

public:
    RigidBody(float mass, glm::vec2 size, glm::vec2 pos, glm::vec2 rot);
    RigidBody();
    ~RigidBody();

    RigidBody(const RigidBody& obj) = delete;

    void update(float dt);


    void applyForce(glm::vec2 force);
    void applyForce(glm::vec2 direction, float magnitude);
    void applyAcceleration(glm::vec2 a);
    void applyAcceleration(glm::vec2 direction, float magnitude);
};

#endif //PHYSICS_ENGINE_RIGIDBODY_H
