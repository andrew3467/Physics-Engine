//
// Created by apgra on 9/6/2023.
//

#include <World.h>

World* World::Instance= nullptr;


void World::createBoxParticle() {
    RigidBody rb = {
            {0.0f, 0.0f},
            {0.0f, 0.0f},
            0.0f,
            0.0f,
            {0.0f, 0.0f},
            0.0f
    };
    m_BoxParticles.emplace_back(1, 1, 1, rb);
    ParticleDrawer::getInstance()->addParticle(rb);
}
