//
// Created by apgra on 9/5/2023.
//

#include "ParticleDrawer.h"
#include "Primitives.h"

ParticleDrawer::ParticleDrawer() {
    m_Shader = std::make_unique<Shader>("../shaders/particle.vert", "../shaders/particle.frag");
}

void ParticleDrawer::drawCircle(float radius, int resolution, glm::mat4 viewProj) {
    for (int i = 0; i < resolution; i++) {
        float x = radius * glm::sin((2 * glm::pi<float>() * i) / resolution);
        float y = radius * glm::cos((2 * glm::pi<float>() * i) / resolution);


        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0));

        m_Shader->bind();
        m_Shader->setMat4("mvp", viewProj * model);
        m_Shader->setVec3("color", 1.0f);

        DrawSquare();

        m_Shader->unbind();
    }
}
