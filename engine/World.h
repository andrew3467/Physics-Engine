//
// Created by Andrew Graser on 9/6/2023.
//

#ifndef PHYSICS_ENGINE_WORLD_H
#define PHYSICS_ENGINE_WORLD_H


#include <vector>
#include "RigidBody.h"

class World {
private:
    static World* m_Instance;


    World(){

    }

public:
    World(const World& obj) = delete;

    static World* getInstance(){
        return m_Instance;
    }

private:
    std::vector<RigidBody> rigidBodies;

public:

};


#endif //PHYSICS_ENGINE_WORLD_H
