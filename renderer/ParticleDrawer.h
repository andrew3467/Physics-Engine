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
#include "Barrier.h"


class ParticleDrawer {
    //Singleton
private:
    static ParticleDrawer* Instance;

    ParticleDrawer() {
        particleShader = std::make_unique<Shader>("../shaders/particle.vert", "../shaders/particle.frag");
        solidUnlitShader = std::make_unique<Shader>("../shaders/solid_unlit.vert", "../shaders/solid_unlit.frag");
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
    std::unique_ptr<Shader> particleShader;
    std::unique_ptr<Shader> solidUnlitShader;

public:

    void drawParticles(glm::mat4 viewProj, std::vector<BoxParticle> particles){
        for(auto particle : particles){
            glm::mat4 model = glm::translate(glm::mat4(1.0f), {particle.rigidBody.position, 0.0f});
            model = glm::scale(model, glm::vec3(particle.Size(), 1.0f));

            particleShader->bind();
            particleShader->setMat4("mvp", viewProj * model);
            particleShader->setVec3("color", 1.0f);
            DrawSquare();
            particleShader->unbind();
        }
    }

    void drawBarriers(glm::mat4 viewProj, std::vector<Barrier> barriers){
        for(auto& barrier : barriers) {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), {barrier.Position, 0.0f});
            model = glm::scale(model, glm::vec3(barrier.Size, 1.0f));

            solidUnlitShader->bind();
            solidUnlitShader->setMat4("mvp", viewProj * model);
            solidUnlitShader->setVec3("color", 1.0f);
            DrawSquare();
            solidUnlitShader->unbind();
        }
    }
};


#endif //PHYSICS_ENGINE_PARTICLEDRAWER_H
