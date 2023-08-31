//
// Created by apgra on 8/31/2023.
//

#ifndef PHYSICS_ENGINE_APPLICATION_H
#define PHYSICS_ENGINE_APPLICATION_H

#include <glfw/glfw3.h>


class Application {
private:
    GLFWwindow* m_Window;
    int m_Width, m_Height;
    const char* m_Title;


public:
    Application(const char* title, int width = 1280, int height = 720);

    void Run();


private:
    void setupWindow();
};


#endif //PHYSICS_ENGINE_APPLICATION_H
