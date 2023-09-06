//
// Created by Andrew Graser on 9/3/2023.
//

#include "Camera.h"

Camera::Camera(glm::vec3 pos, int windowWidth, int windowHeight) : windowWidth(windowWidth), windowHeight(windowHeight), camPos(pos) {

}

void Camera::move(CameraMoveDir moveDir, float deltaTime) {
    switch(moveDir) {
        case Right:
            camPos += glm::normalize(glm::cross(camFront, camUp)) * camSpeed * deltaTime;
            break;
        case Left:
            camPos -= glm::normalize(glm::cross(camFront, camUp)) * camSpeed * deltaTime;
            break;
        case Back:
            camPos -= camSpeed * camFront * deltaTime;
            break;
        case Forward:
            camPos += camSpeed * camFront * deltaTime;
            break;
        case Up:
            camPos += camSpeed * camUp * deltaTime;
            break;
        case Down:
            camPos -= camSpeed * camUp * deltaTime;
            break;
    }
}