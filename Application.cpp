//
// Created by apgra on 8/31/2023.
//

#include <glad/glad.h>
#include "Application.h"

#include <stdexcept>

Application::Application(const char *title, int width, int height) : m_Title(title), m_Width(width), m_Height(height) {
    setupWindow();
}

void Application::setupWindow() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, nullptr, nullptr);

    if(!m_Window){
        glfwTerminate();
        throw std::runtime_error("ERROR: Failed to create GLFW window");
    }
    glfwMakeContextCurrent(m_Window);


    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
        throw std::runtime_error("ERROR: Failed to initialize GLAD");
    }
}

void Application::Run() {

    while(!glfwWindowShouldClose(m_Window)){
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glfwSwapBuffers(m_Window);



        glfwPollEvents();
    }
}
