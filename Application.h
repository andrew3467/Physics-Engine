//
// Created by apgra on 8/31/2023.
//

#ifndef PHYSICS_ENGINE_APPLICATION_H
#define PHYSICS_ENGINE_APPLICATION_H

#define GLFW_INCLUDE_NONE

#include <glfw/glfw3.h>
#include <memory>
#include "Camera.h"
#include "Shader.h"


struct LineConfig{
    int length = 1;
    glm::ivec2 pos = {0, 0};
    glm::vec2 velocity = {0.0f, 0.0f};
    bool isVertical = false;
};

class Application {
private:
    GLFWwindow* m_Window;
    int m_Width, m_Height;
    const char* m_Title;

    LineConfig lineConfig;


public:
    Application(const char* title, int width = 1280, int height = 720);

    void Run();

private:
    void setupWindow();

    void processInput(GLFWwindow* window);

    void onImGUIRender();

    void CreateLine(LineConfig config);
};


#endif //PHYSICS_ENGINE_APPLICATION_H
