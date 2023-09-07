//
// Created by apgra on 8/31/2023.
//

#include "Application.h"
#include "BoxParticle.h"
#include "World.h"
#include "Random.h"

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

//Toggles
bool clickToPlaceParticle = false;



void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void window_resize_callback(GLFWwindow* window, int width, int height);




Application::Application(const char *title, int width, int height) : m_Title(title), WindowSize(width, height) {
    setupWindow();
}

void Application::setupWindow() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = glfwCreateWindow(WindowSize.x, WindowSize.y, m_Title, nullptr, nullptr);
    glfwSetWindowUserPointer(m_Window, this);

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
    camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 4.0f), WindowSize.x, WindowSize.y);

    //GLFW Callbacks
    glfwSetKeyCallback(m_Window, key_callback);
    glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
    glfwSetWindowSizeCallback(m_Window, window_resize_callback);



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

    //Create Barriers
    World::getInstance()->createBarrier(
            {0.0f, WindowSize.y / 2},
            {WindowSize.x, 2.0f}
            );


    glViewport(0, 0, WindowSize.x, WindowSize.y);
    while(!glfwWindowShouldClose(m_Window)){
        glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        processInput();

        //Update Particles
        World::getInstance()->update(deltaTime);

        //Render scene
        ParticleDrawer::getInstance()->drawBarriers(camera->viewProjection(), World::getInstance()->GetBarriers());
        ParticleDrawer::getInstance()->drawParticles(camera->viewProjection(), World::getInstance()->GetBoxParticles());


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
        World::getInstance()->clearParticles();
    }

    ImGui::Checkbox("Click To Place", &clickToPlaceParticle);

    if(ImGui::CollapsingHeader("Particle Configs")){
        ImGui::Indent();
        ImGui::Checkbox("Gravity", &particleConfig.hasGravity);
        ImGui::SliderFloat2("Size", &particleConfig.size.x, 0.5f, 10);
        ImGui::SliderFloat2("Velocity", &particleConfig.velocity.x, -10, 10);
        ImGui::SliderFloat2("Velocity Variation", &particleConfig.velocityVariation.x, -2.0f, 2.0f);
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
                ImGui::SliderFloat2("Velocity", &boxParticles[i].rigidBody.linearVelocity.x, -2.0f, 2.0f);
            }
        }
    }

    if(ImGui::CollapsingHeader("Particle Line")){
        ImGui::SliderInt("Length", &lineConfig.length, 1, 50);
        ImGui::SliderInt2("position", &lineConfig.pos.x, -10, 10);
        ImGui::Checkbox("Vertical", &lineConfig.isVertical);


        if(ImGui::Button("Create Line")){
            CreateLine();
        }
    }

    if(ImGui::CollapsingHeader("Particle Grid")){
        ImGui::SliderInt2("Size", &gridConfig.size.x, 1, 50);
        ImGui::SliderInt2("Position", &lineConfig.pos.x, -10, 10);

        if(ImGui::Button("Create Grid")){
            CreateGrid();
        }
    }


}
void Application::CreateLine() {
    for(int i = -lineConfig.length / 2; i < lineConfig.length / 2; i++){
        glm::vec2 position = {(i + lineConfig.pos.x) * particleConfig.size.x, lineConfig.pos.y * particleConfig.size.y};

        if(lineConfig.isVertical){
            position = {lineConfig.pos.x, i + lineConfig.pos.y};
        }

        RigidBody rb = {
                position,
                {
                        particleConfig.velocity.x + (particleConfig.velocityVariation.x * (Random::Float() - 0.5f)),
                        particleConfig.velocity.y + (particleConfig.velocityVariation.y * (Random::Float() - 0.5f))
                },
                {0.0f, 0.0f},
                0.0f,
                0.0f,
                glm::vec2(0.0f),
                0.0f,
                particleConfig.hasGravity
        };

        World::getInstance()->createBoxParticle(particleConfig.size.x, particleConfig.size.y, 1.0f, rb);
    }
}

void Application::CreateGrid() {
    for(int y = -gridConfig.size.y / 2; y < gridConfig.size.y / 2; y++) {
        for (int x = -gridConfig.size.x / 2; x < gridConfig.size.x / 2; x++) {
            glm::vec2 position = {(x + lineConfig.pos.x) * particleConfig.size.x, (y + lineConfig.pos.y) * particleConfig.size.y};

            RigidBody rb = {
                    position,
                    {
                            particleConfig.velocity.x + (particleConfig.velocityVariation.x * (Random::Float() - 0.5f)),
                            particleConfig.velocity.y + (particleConfig.velocityVariation.y * (Random::Float() - 0.5f))
                    },
                    {0.0f, 0.0f},
                    0.0f,
                    0.0f,
                    glm::vec2(0.0f),
                    0.0f,
                    particleConfig.hasGravity
            };

            World::getInstance()->createBoxParticle(particleConfig.size.x, particleConfig.size.y, 1.0f, rb);
        }
    }
}

void Application::updateWindowSize(int width, int height) {
    WindowSize.x = width;
    WindowSize.y = height;
}

glm::vec2 screenSpaceToWorldSpace(glm::vec2 screenCoords, glm::mat4 viewProj, glm::vec2 windowSize){
    glm::mat4 invViewProj = glm::mat4(1.0f) / viewProj;
    glm::vec4 In = {
            2.0f * (screenCoords.x / windowSize.x) - 1.0f,
            1.0f - (2.0f * screenCoords.y / windowSize.y),
            0.0f,
            1.0f
    };

    auto pos = In * invViewProj;

    pos.w = 1 / pos.w;

    pos.x *= pos.w;
    pos.y *= pos.w;
    pos.z *= pos.w;

    return pos;
}



void Application::processInput(){
    if (glfwGetKey(m_Window, GLFW_KEY_A)){
        color -= glm::vec3(1.0f, 1.0f, 0.0f);
        camera->move(Left, deltaTime);
    }

    if (glfwGetKey(m_Window, GLFW_KEY_D)){
        color += glm::vec3(1.0f, 0.0f, 1.0f);
        camera->move(Right, deltaTime);
    }

    if (glfwGetKey(m_Window, GLFW_KEY_S)){
        camera->move(Down, deltaTime);
    }

    if (glfwGetKey(m_Window, GLFW_KEY_W)){
        camera->move(Up, deltaTime);
    }

    if (glfwGetKey(m_Window, GLFW_KEY_LEFT_CONTROL)){
        camera->move(Back, deltaTime);
    }

    if (glfwGetKey(m_Window, GLFW_KEY_LEFT_SHIFT)){
        camera->move(Forward, deltaTime);
    }    
}

//Callbacks
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if(clickToPlaceParticle && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        double xpos, ypos;
        //getting cursor position
        glfwGetCursorPos(window, &xpos, &ypos);
        glm::vec2 worldCoord = screenSpaceToWorldSpace({xpos, ypos}, camera->viewProjection(), {1280, 720});

        RigidBody rb;
        rb.position.x = worldCoord.x;
        rb.position.y = worldCoord.y;

        World::getInstance()->createBoxParticle(1, 1, 1, rb);
    }
}

void window_resize_callback(GLFWwindow* window, int width, int height){
    Application* app = (Application*)(glfwGetWindowUserPointer(window));

    glViewport(0, 0, width, height);
    app->updateWindowSize(width, height);
}
