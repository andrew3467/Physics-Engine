//
// Created by apgra on 9/5/2023.
//

#ifndef PHYSICS_ENGINE_PARTICLEDRAWER_H
#define PHYSICS_ENGINE_PARTICLEDRAWER_H


#include <glm/glm.hpp>
#include <Shader.h>
#include <memory>
#include "Particle.h"


class ParticleDrawer {
private:
    std::unique_ptr<Shader> m_Shader;

    std::vector<Particle> m_Particles;

public:
    ParticleDrawer();

    void clear();

    void ImGuiConfigWindow();

    void createParticle(glm::vec3 position, glm::vec3 velocity, glm::vec3 acceleration);
    void createParticle();

    void drawParticles(glm::mat4 viewProj);
    void update(float deltaTime);


    std::vector<Particle> particles() { return m_Particles;}
};


#endif //PHYSICS_ENGINE_PARTICLEDRAWER_H
