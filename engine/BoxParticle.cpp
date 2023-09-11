//
// Created by Andrew Graser on 9/6/2023.
//

#include <glm/vec2.hpp>
#include "BoxParticle.h"
#include "World.h"


void BoxParticle::update(float deltaTime) {
    rigidBody->update(deltaTime);
}

BoxParticle::BoxParticle(float mass, glm::vec2 size, glm::vec2 pos, glm::vec2 rot) {
    rigidBody = new RigidBody(mass, size, pos, rot);
}

BoxParticle::BoxParticle() {
    rigidBody = new RigidBody(1.0f, glm::vec2(1.0f), glm::vec2(0.0f), glm::vec2(0.0f));
}
