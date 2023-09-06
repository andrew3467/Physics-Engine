//
// Created by Andrew Graser on 9/6/2023.
//

#include <glm/vec2.hpp>
#include "BoxParticle.h"

BoxParticle::BoxParticle(float w, float h, float m, RigidBody rb) : width(w), height(h), mass(m), rigidBody(rb) {
    calculateMomentOfInertia();
}



void BoxParticle::calculateMomentOfInertia() {
    momentOfInertia = mass * (width * width - height * height) / 12;
}

void BoxParticle::update(float deltaTime) {
    glm::vec2 force = {0, mass * -9.81};
    glm::vec2 acceleration(force.x / mass, force.y / mass);
    rigidBody.linearVelocity += acceleration * deltaTime;
    rigidBody.position += rigidBody.linearVelocity * deltaTime;
}