//
// Created by Andrew Graser on 9/6/2023.
//

#ifndef PHYSICS_ENGINE_BOXPARTICLE_H
#define PHYSICS_ENGINE_BOXPARTICLE_H


#include "RigidBody.h"

class BoxParticle {
private:
    float width;
    float height;
    float mass;
    float momentOfInertia;

public:
    RigidBody rigidBody;


public:
    BoxParticle(float w, float h, float m, RigidBody rb);

    void update(float deltaTime);

private:
    void calculateMomentOfInertia();
};


#endif //PHYSICS_ENGINE_BOXPARTICLE_H