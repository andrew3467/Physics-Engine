//
// Created by apgra on 8/31/2023.
//

#ifndef PHYSICS_ENGINE_APPLICATION_H
#define PHYSICS_ENGINE_APPLICATION_H

#include <glfw/glfw3.h>
#include <memory>
#include "Camera.h"


class Application {
private:
    GLFWwindow* m_Window;
    int m_Width, m_Height;
    const char* m_Title;


public:
    Application(const char* title, int width = 1280, int height = 720);

    void Run();

    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);


private:
    void setupWindow();
};


#endif //PHYSICS_ENGINE_APPLICATION_H
