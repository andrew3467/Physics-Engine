//
// Created by Andrew Graser on 9/3/2023.
//

#ifndef PHYSICS_ENGINE_CAMERA_H
#define PHYSICS_ENGINE_CAMERA_H


#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

enum CameraMoveDir{
    Right = 0,
    Left = 1,
    Back = 2,
    Forward = 3,
    Up = 4,
    Down = 5
};

class Camera {
private:
    int windowWidth;
    int windowHeight;

    float camSpeed = 10.0;

    glm::vec3 camPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 camFront = glm::vec3(0.0f, 0.0f, -1.0f);

    glm::vec3 camTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 camDir = glm::normalize(camPos - camTarget);

    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 camRight = glm::normalize(glm::cross(up, camDir));
    glm::vec3 camUp = glm::cross(camDir, camRight);


public:
    Camera();
    Camera(glm::vec3 pos, int windowWidth, int windowHeight);



    void move(CameraMoveDir moveDir, float deltaTime);

    inline glm::mat4 viewProjection() const {return projection() * view();}
    inline glm::mat4 projection() const {return glm::perspective(glm::radians(60.0f),
                                                                 (float)windowWidth / (float)windowHeight,0.1f, 100.0f);}


    inline glm::mat4 view() const {return glm::lookAt(camPos, center(), camUp);}
    inline glm::vec3 position() const {return camPos;}
    inline glm::vec3 front() const {return camFront;}
    inline glm::vec3 center() const {return camPos + camFront;}
    inline glm::vec3 cameraUp() const {return camUp;}
};


#endif //PHYSICS_ENGINE_CAMERA_H
