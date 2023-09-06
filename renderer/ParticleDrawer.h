//
// Created by apgra on 9/5/2023.
//

#ifndef PHYSICS_ENGINE_PARTICLEDRAWER_H
#define PHYSICS_ENGINE_PARTICLEDRAWER_H


#include <glm/glm.hpp>
#include "Primitives.h"
#include <Shader.h>
#include <memory>
#include <glm/gtx/string_cast.hpp>
#include "BoxParticle.h"


class ParticleDrawer {
    //Singleton
private:
    static ParticleDrawer* Instance;

    ParticleDrawer() {
        m_Shader = std::make_unique<Shader>("../shaders/particle.vert", "../shaders/particle.frag");
    }

public:
    ParticleDrawer(const ParticleDrawer& obj) = delete;

    static ParticleDrawer* getInstance(){
        if (Instance == nullptr)
        {
            Instance = new ParticleDrawer();
        }
        return Instance;
    }



private:
    std::unique_ptr<Shader> m_Shader;

    std::vector<RigidBody> m_Particles;

public:


    void clear() {
        m_Particles.clear();
    }

    void addParticle(RigidBody p) {
        m_Particles.push_back(p);
    }

    void drawParticles(glm::mat4 viewProj){
        for(auto rb : m_Particles){
            glm::mat4 model = glm::translate(glm::mat4(1.0f), {rb.position, 0.0f});

            m_Shader->bind();
            m_Shader->setMat4("mvp", viewProj * model);
            m_Shader->setVec3("color", 1.0f);
            DrawSquare();
            m_Shader->unbind();
        }
    }


    std::vector<RigidBody> particlesRBs() { return m_Particles;}
};


#endif //PHYSICS_ENGINE_PARTICLEDRAWER_H
