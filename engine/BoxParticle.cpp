//
// Created by Andrew Graser on 9/6/2023.
//

#include <glm/vec2.hpp>
#include "BoxParticle.h"
#include "World.h"


#define GRAVITY -9.81


BoxParticle::BoxParticle(float w, float h, float m, RigidBody rb) : width(w), height(h), mass(m), rigidBody(rb) {

}



float BoxParticle::calculateMomentOfInertia() {
    return mass * (width * width - height * height) / 12;
}

void BoxParticle::update(float deltaTime) {

    //Force
    rigidBody.force = {0, mass};
    if(rigidBody.hasGravity){
        rigidBody.force.y *= GRAVITY;
    }

    //Torque
    glm::vec2 r = {
            width / 2,
            height / 2
    };
    rigidBody.torque = r.x * rigidBody.force.y - r.y * rigidBody.force.x;

    rigidBody.linearAcceleration = rigidBody.force / mass;
    rigidBody.linearVelocity += rigidBody.linearAcceleration * deltaTime;

    //Check for collision
    //Loop over all other particles in scene
    for(auto& other : World::getInstance()->GetBoxParticles()){
        //Collision
        //Temp invert velocity
        if(AABB::TestOverlap(this->rigidBody.aabb, other.rigidBody.aabb)){
            rigidBody.linearVelocity *= -1;
        }
    }


    rigidBody.position += rigidBody.linearVelocity * deltaTime;
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
