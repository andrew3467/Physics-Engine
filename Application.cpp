//
// Created by apgra on 8/31/2023.
//

#include <glad/glad.h>
#include "Application.h"
#include "renderer/Shader.h"
#include "Primitives.h"

#include <stdexcept>
#include <iostream>


float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
};

unsigned int indices[] = {
        0, 1, 2
};

unsigned int VAO, VBO, EBO;

std::unique_ptr<Camera> camera;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

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

glm::vec3 color = glm::vec3(1.0f);

void Application::Run() {
    //Setup callbacks
    glfwSetKeyCallback(m_Window, key_callback);

    Shader shader("../shaders/solid_unlit.glsl");

    camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, -1.0f), m_Width, m_Height);




    glViewport(0, 0, m_Width, m_Height);
    while(!glfwWindowShouldClose(m_Window)){
        glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glm::mat4 model(1.0f);
        model = glm::scale(model, glm::vec3(1.0f) * deltaTime);


        shader.bind();

        shader.setMat4("mvp", camera->viewProjection() * model);

        shader.setVec3("color", color);

        DrawSquare();




        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }
}

void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }

    if (key == GLFW_KEY_A && action == GLFW_PRESS){
        color = glm::vec3(1.0f, 1.0f, 0.0f);
        camera->move(Left, deltaTime);
    }

    if (key == GLFW_KEY_D && action == GLFW_PRESS){
        color = glm::vec3(1.0f, 0.0f, 1.0f);
        camera->move(Right, deltaTime);
    }

}
