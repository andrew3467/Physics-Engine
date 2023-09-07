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
#include <World.h>


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

public:

    void drawParticles(glm::mat4 viewProj, std::vector<BoxParticle> particles){
        for(auto particle : particles){
            glm::mat4 model = glm::translate(glm::mat4(1.0f), {particle.rigidBody.position, 0.0f});
            model = glm::scale(model, glm::vec3(particle.Size(), 1.0f));

            m_Shader->bind();
            m_Shader->setMat4("mvp", viewProj * model);
            m_Shader->setVec3("color", 1.0f);
            DrawSquare();
            m_Shader->unbind();
        }
    }
};


#endif //PHYSICS_ENGINE_PARTICLEDRAWER_H
