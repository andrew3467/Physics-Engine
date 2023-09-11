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

    void createBoxParticle(float mass, glm::vec2 size, glm::vec2 pos, glm::vec2 rot) {
        m_BoxParticles.emplace_back(mass, size, pos, rot);
    }

    void createBoxParticle(){
        m_BoxParticles.emplace_back();
    }

    void createBarrier(glm::vec2 pos, glm::vec2 size){
        m_Barriers.push_back({pos, size});
    }
};


#endif //PHYSICS_ENGINE_WORLD_H
