//
// Created by Andrew Graser on 9/6/2023.
//

#include <glm/vec2.hpp>
#include "BoxParticle.h"


#define GRAVITY -9.81


BoxParticle::BoxParticle(float w, float h, float m, RigidBody rb) : width(w), height(h), mass(m), rigidBody(rb) {
    calculateMomentOfInertia();
}



float BoxParticle::calculateMomentOfInertia() {
    return mass * (width * width - height * height) / 12;
}

void BoxParticle::update(float deltaTime) {
    glm::vec2 force = {0, mass};
    if(rigidBody.hasGravity){
        force.y *= GRAVITY;
    }


    //Force
    rigidBody.force = {0, 100};

    //Torque
    glm::vec2 r = {
            width / 2,
            height / 2
    };
    rigidBody.torque = r.x * rigidBody.force.y - r.y * rigidBody.force.x;

    rigidBody.linearAccceleration = rigidBody.force / mass;
    rigidBody.linearVelocity = rigidBody.linearAccceleration * deltaTime;
    rigidBody.position = rigidBody.linearVelocity * deltaTime;
    float angularAcceleration = rigidBody.torque / calculateMomentOfInertia();
    rigidBody.angularVelocity += angularAcceleration * deltaTime;
    rigidBody.angle += rigidBody.angularVelocity * deltaTime;
}

glm::vec2 BoxParticle::Size() {
    return {
      width,
      height
    };
}
