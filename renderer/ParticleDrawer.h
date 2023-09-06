//
// Created by apgra on 9/5/2023.
//

#ifndef PHYSICS_ENGINE_PARTICLEDRAWER_H
#define PHYSICS_ENGINE_PARTICLEDRAWER_H


#include <glm/glm.hpp>
#include <Shader.h>
#include <memory>
#include "BoxParticle.h"


class ParticleDrawer {
private:
    std::unique_ptr<Shader> m_Shader;

    std::vector<BoxParticle> m_BoxParticles;

public:
    ParticleDrawer();

    void clear();

    void ImGuiConfigWindow();

    void addParticle(BoxParticle p);
    void createParticle();

    void drawParticles(glm::mat4 viewProj);
    void update(float deltaTime);


    std::vector<BoxParticle> particles() { return m_BoxParticles;}
};


#endif //PHYSICS_ENGINE_PARTICLEDRAWER_H
