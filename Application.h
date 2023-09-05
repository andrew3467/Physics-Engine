//
// Created by apgra on 8/31/2023.
//

#ifndef PHYSICS_ENGINE_APPLICATION_H
#define PHYSICS_ENGINE_APPLICATION_H

#include <glfw/glfw3.h>
#include <memory>
#include "Camera.h"
#include "Shader.h"
#include "ParticleDrawer.h"


class Application {
private:
    GLFWwindow* m_Window;
    int m_Width, m_Height;
    const char* m_Title;

    std::unique_ptr<ParticleDrawer> particleDrawer;


public:
    Application(const char* title, int width = 1280, int height = 720);

    void Run();

private:
    void setupWindow();

    void processInput(GLFWwindow* window);

    void onImGUIRender();
};


#endif //PHYSICS_ENGINE_APPLICATION_H
