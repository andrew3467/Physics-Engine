//
// Created by apgra on 8/31/2023.
//

#include <glad/glad.h>
#include "Application.h"
#include "renderer/Shader.h"
#include "Primitives.h"

#include <stdexcept>
#include <iostream>
#include <glm/gtx/string_cast.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


std::unique_ptr<Camera> camera;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

float circleRadius = 2.0f;
int circleResolution = 2;

glm::vec3 color = glm::vec3(1.0f);

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
    Shader shader("../shaders/solid_unlit.vert", "../shaders/solid_unlit.frag");

    camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 4.0f), m_Width, m_Height);
    particleDrawer = std::make_unique<ParticleDrawer>();

    //Setup IMGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui::StyleColorsDark();

    const char* glsl_version = "#version 460";
    ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);


    glViewport(0, 0, m_Width, m_Height);
    while(!glfwWindowShouldClose(m_Window)){
        glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        processInput(m_Window);

        //Render scene
        particleDrawer->drawCircle(circleRadius, circleResolution, camera->viewProjection());


        //Draw ImGui Windows
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        ImGui::Begin("Config Window");
        onImGUIRender();



        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}


void Application::onImGUIRender() {
    ImGui::SliderFloat("Circle Radius", &circleRadius, 1.0f, 10.0f);
    ImGui::SliderInt("Circle Resolution", &circleResolution, 1.0f, 100.0f);
}

void Application::processInput(GLFWwindow* window) {

    if(glfwGetKey(window, GLFW_KEY_ESCAPE)){
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_A)){
        color -= glm::vec3(1.0f, 1.0f, 0.0f);
        camera->move(Left, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_D)){
        color += glm::vec3(1.0f, 0.0f, 1.0f);
        camera->move(Right, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_S)){
        camera->move(Back, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE)){
        std::cout << glm::to_string(camera->position()) << "\n\n";
    }
}
