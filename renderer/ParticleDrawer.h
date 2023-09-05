//
// Created by apgra on 9/5/2023.
//

#ifndef PHYSICS_ENGINE_PARTICLEDRAWER_H
#define PHYSICS_ENGINE_PARTICLEDRAWER_H


#include <glm/glm.hpp>
#include <Shader.h>
#include <memory>



class ParticleDrawer {
private:
    std::unique_ptr<Shader> m_Shader;

public:
    ParticleDrawer();

    void drawCircle(float radius, int resolution, glm::mat4 viewProj);
};


#endif //PHYSICS_ENGINE_PARTICLEDRAWER_H
