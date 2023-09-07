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
    bool isVertical = false;
};

struct GridConfig{
    glm::ivec2 size = {1, 1};
    glm::ivec2 pos = {0, 0};
};

struct ParticleConfig{
    glm::vec2 size = {1, 1};
    glm::vec2 velocity = {0.0f, 0.0f};
    glm::vec2 velocityVariation = {0.0f, 0.0f};
    bool hasGravity;
};

class Application {
private:
    GLFWwindow* m_Window;
    const char* m_Title;

    LineConfig lineConfig;
    GridConfig gridConfig;
    ParticleConfig particleConfig;

public:
    glm::ivec2 WindowSize;

public:
    Application(const char* title, int width = 1280, int height = 720);

    void updateWindowSize(int width, int height);

    void Run();

private:
    void setupWindow();


    void onImGUIRender();

    void CreateLine();
    void CreateGrid();

    void processInput();
};


#endif //PHYSICS_ENGINE_APPLICATION_H
