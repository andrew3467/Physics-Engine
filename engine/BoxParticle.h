//
// Created by Andrew Graser on 9/6/2023.
//

#ifndef PHYSICS_ENGINE_BOXPARTICLE_H
#define PHYSICS_ENGINE_BOXPARTICLE_H


#include "RigidBody.h"

class BoxParticle {
private:

public:
    RigidBody *rigidBody;


public:
    BoxParticle(float mass, glm::vec2 size, glm::vec2 pos, glm::vec2 rot);
    BoxParticle();

    void update(float deltaTime);

private:

};


#endif //PHYSICS_ENGINE_BOXPARTICLE_H
