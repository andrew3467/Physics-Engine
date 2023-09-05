//
// Created by apgra on 9/5/2023.
//

#include "Particle.h"

Particle::Particle() : Position(0.0f), InitialVelocity(0.0f), Acceleration(0.0f), Velocity(InitialVelocity) {

}

Particle::Particle(glm::vec3 position, glm::vec3 velocity, glm::vec3 acceleration) :
        Position(position), InitialVelocity(velocity), Acceleration(acceleration), Velocity(InitialVelocity)
{

}
