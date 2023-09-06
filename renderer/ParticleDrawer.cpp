//
// Created by apgra on 9/5/2023.
//

#include <imgui.h>
#include <glm/gtx/string_cast.hpp>
#include "ParticleDrawer.h"
#include "Primitives.h"

ParticleDrawer::ParticleDrawer() {
    m_Shader = std::make_unique<Shader>("../shaders/particle.vert", "../shaders/particle.frag");
}

void ParticleDrawer::clear() {
    m_BoxParticles.clear();
}

void ParticleDrawer::addParticle(BoxParticle p) {
    m_BoxParticles.push_back(p);
}

void ParticleDrawer::createParticle() {
    m_BoxParticles.emplace_back(1, 1, 1);
}

void ParticleDrawer::drawParticles(glm::mat4 viewProj) {
    for(auto p : m_BoxParticles){
        glm::mat4 model = glm::translate(glm::mat4(1.0f), {p.position, 0.0f});

        m_Shader->bind();
        m_Shader->setMat4("mvp", viewProj * model);
        m_Shader->setVec3("color", 1.0f);
        DrawSquare();
        m_Shader->unbind();
    }
}

void ParticleDrawer::ImGuiConfigWindow() {
    for(int i = 0; i < m_BoxParticles.size(); i++){
        if(ImGui::CollapsingHeader(("Particle #" + std::to_string(i)).c_str())){
            ImGui::Indent();
            ImGui::SliderFloat2("position", &m_BoxParticles[i].position.x, -10.0f, 10.0f);
            ImGui::SliderFloat2("InitialVelocity", &m_BoxParticles[i].velocity.x, -2.0f, 2.0f);
        }
    }
}

void ParticleDrawer::update(float deltaTime) {
    for(auto &particle : m_BoxParticles){
        particle.update(deltaTime);
    }
}
