//
// Created by apgra on 8/31/2023.
//

#include "Application.h"
#include "BoxParticle.h"
#include "World.h"
#include "ParticleDrawer.h"

#include <stdexcept>
#include <iostream>
#include <glm/gtx/string_cast.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


std::unique_ptr<Camera> camera;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

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
        ParticleDrawer::getInstance()->drawParticles(camera->viewProjection());


        //Draw ImGui Windows
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        ImGui::Begin("Config Window");
        onImGUIRender();



        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        World::getInstance()->update(deltaTime);


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
    if(ImGui::Button("Clear particles")){
        ParticleDrawer::getInstance()->clear();
    }

    if(ImGui::CollapsingHeader("Manual Particle Config")){
        ImGui::Indent();
        if (ImGui::Button("Create Particle")) {
            World::getInstance()->createBoxParticle();
        }


        auto& boxParticles = World::getInstance()->GetBoxParticles();
        for(int i = 0; i < boxParticles.size(); i++){
            if(ImGui::CollapsingHeader(("Particle #" + std::to_string(i)).c_str())){
                ImGui::Indent();
                ImGui::SliderFloat2("position", &boxParticles[i].rigidBody.position.x, -10.0f, 10.0f);
                ImGui::SliderFloat2("InitialVelocity", &boxParticles[i].rigidBody.linearVelocity.x, -2.0f, 2.0f);
            }
        }
    }

    if(ImGui::CollapsingHeader("Particle Line")){
        ImGui::SliderInt("Length", &lineConfig.length, 1, 50);
        ImGui::SliderInt2("position", &lineConfig.pos.x, -10, 10);
        ImGui::SliderFloat2("velocity", &lineConfig.velocity.x, -10, 10);
        ImGui::Checkbox("Vertical", &lineConfig.isVertical);

        if(ImGui::Button("Create Line")){
            CreateLine(lineConfig);
        }
    }


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
        camera->move(Down, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_W)){
        camera->move(Up, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)){
        camera->move(Back, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)){
        camera->move(Forward, deltaTime);
    }
}

void Application::CreateLine(LineConfig config) {
    for(int i = -config.length / 2; i < config.length / 2; i++){
        glm::vec2 position = {i + config.pos.x, config.pos.y};;

        if(config.isVertical){
            position = {config.pos.x, i + config.pos.y};
        }

        RigidBody rb = {
                position,
                config.velocity,
                0.0f,
                0.0f,
                glm::vec2(0.0f),
                0.0f
        };

        World::getInstance()->createBoxParticle(1.0f, 1.0f, 1.0f, rb);
    }
}
