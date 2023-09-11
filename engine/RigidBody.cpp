//
// Created by Andrew Graser on 9/10/2023.
//
#include <iostream>
#include "RigidBody.h"


#define GRAVITY -9.81


RigidBody::RigidBody(float mass, glm::vec2 size,  glm::vec2 pos, glm::vec2 rot) : mass(mass), size(size), position(pos), rotation(rot) {

}

RigidBody::RigidBody() : mass(0.0f), position(0.0f), rotation(0.0f){

}

RigidBody::~RigidBody() {

}

void RigidBody::update(float dt) {
    position += velocity * dt + 0.5f * acceleration * (dt * dt);
    velocity += acceleration * dt;

    //rotation matrix
    glm::mat4 rotMat = glm::toMat4(glm::quat(glm::vec3(rotation, 0.0f)));


    model = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0));
    model = model * rotMat;
    model = glm::scale(model, glm::vec3(size, 1.0f));
}

void RigidBody::applyForce(glm::vec2 force) {
    acceleration += force / mass;
}

void RigidBody::applyForce(glm::vec2 direction, float magnitude) {
    applyForce(direction * magnitude);
}

void RigidBody::applyAcceleration(glm::vec2 a) {
    acceleration += a;
}

void RigidBody::applyAcceleration(glm::vec2 direction, float magnitude) {

}



