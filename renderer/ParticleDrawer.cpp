//
// Created by apgra on 9/5/2023.
//

#include <imgui.h>
#include "ParticleDrawer.h"
#include "Primitives.h"

ParticleDrawer::ParticleDrawer() {
    m_Shader = std::make_unique<Shader>("../shaders/particle.vert", "../shaders/particle.frag");
}

void ParticleDrawer::clear() {
    m_Particles.clear();
}

void ParticleDrawer::createParticle(glm::vec3 position, glm::vec3 velocity, glm::vec3 acceleration) {
    m_Particles.emplace_back(position, velocity, acceleration);
}

void ParticleDrawer::createParticle() {
    m_Particles.push_back(Particle());
}

void ParticleDrawer::drawParticles(glm::mat4 viewProj) {
    for(auto p : m_Particles){
        glm::mat4 model = glm::translate(glm::mat4(1.0f), p.Position);

        m_Shader->bind();
        m_Shader->setMat4("mvp", viewProj * model);
        m_Shader->setVec3("color", 1.0f);
        DrawSquare();
        m_Shader->unbind();
    }
}

void ParticleDrawer::ImGuiConfigWindow() {
    for(int i = 0; i < m_Particles.size(); i++){
        if(ImGui::CollapsingHeader(("Particle #" + std::to_string(i)).c_str())){
            ImGui::Indent();
            ImGui::SliderFloat3("Position", &m_Particles[i].Position.x, -10.0f, 10.0f);
            ImGui::SliderFloat3("InitialVelocity", &m_Particles[i].InitialVelocity.x, -2.0f, 2.0f);
            ImGui::SliderFloat3("Acceleration", &m_Particles[i].Acceleration.x, -4.0f, 4.0f);
        }
    }
}
