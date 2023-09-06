//
// Created by Andrew Graser on 9/6/2023.
//

#ifndef PHYSICS_ENGINE_WORLD_H
#define PHYSICS_ENGINE_WORLD_H


#include <vector>
#include "RigidBody.h"
#include "ParticleDrawer.h"

class World {
protected:
    static World* Instance;


    World(){

    }

public:
    World(const World& obj) = delete;

    static World* getInstance(){
        if (Instance == nullptr) {
            Instance = new World();
        }
        return Instance;
    }

    void update(float deltaTime){
        for(auto particle : m_BoxParticles){
            particle.update(deltaTime);
        }
    }

private:
    std::vector<BoxParticle> m_BoxParticles;

public:
    std::vector<BoxParticle>& GetBoxParticles(){
        return m_BoxParticles;
    }

    void createBoxParticle(float w, float h, float m, RigidBody rb){
        m_BoxParticles.emplace_back(w, h, m, rb);
        ParticleDrawer::getInstance()->addParticle(rb);
    }

    void createBoxParticle();
};


#endif //PHYSICS_ENGINE_WORLD_H
