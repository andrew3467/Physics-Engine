//
// Created by apgra on 9/5/2023.
//

#ifndef PHYSICS_ENGINE_PARTICLE_H
#define PHYSICS_ENGINE_PARTICLE_H

#include <glm/glm.hpp>


class Particle {
public:
    glm::vec3 Position;
    glm::vec3 InitialVelocity;
    glm::vec3 Velocity;
    glm::vec3 Acceleration;

public:
    Particle();
    Particle(glm::vec3 position, glm::vec3 velocity, glm::vec3 acceleration);


    void update();
};


#endif //PHYSICS_ENGINE_PARTICLE_H
