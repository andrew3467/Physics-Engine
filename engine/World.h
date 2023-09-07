//
// Created by Andrew Graser on 9/6/2023.
//

#ifndef PHYSICS_ENGINE_WORLD_H
#define PHYSICS_ENGINE_WORLD_H


#include <vector>
#include "RigidBody.h"
#include "ParticleDrawer.h"
#include "Barrier.h"

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
        for(auto &particle : m_BoxParticles){
            particle.update(deltaTime);
        }
    }

private:
    std::vector<BoxParticle> m_BoxParticles;
    std::vector<Barrier> m_Barriers;

public:
    std::vector<BoxParticle>& GetBoxParticles(){
        return m_BoxParticles;
    }

    std::vector<Barrier>& GetBarriers(){
        return m_Barriers;
    }

    void clearParticles(){
        m_BoxParticles.clear();
    }

    void createBoxParticle(float w, float h, float m, RigidBody rb){
        m_BoxParticles.emplace_back(w, h, m, rb);
    }

    void createBoxParticle() {
        RigidBody rb = {
                {0.0f, 0.0f},
                {0.0f, 0.0f},
                {0.0f, 0.0f},
                0.0f,
                0.0f,
                {0.0f, 0.0f},
                0.0f
        };
        m_BoxParticles.emplace_back(1, 1, 1, rb);
    }

    void createBarrier(glm::vec2 pos, glm::vec2 size){
        m_Barriers.push_back({pos, size});
    }
};


#endif //PHYSICS_ENGINE_WORLD_H
