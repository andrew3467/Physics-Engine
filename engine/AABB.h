//
// Created by Andrew Graser on 9/8/2023.
//

#ifndef PHYSICS_ENGINE_AABB_H
#define PHYSICS_ENGINE_AABB_H

#include <glm/vec2.hpp>

class AABB {
public:
    glm::vec2 Min;
    glm::vec2 Max;

    AABB(glm::vec2 min, glm::vec2 max) : Min(min), Max(max){

    }

    AABB() : Min(0.0f), Max(0.0f) {

    }

public:
    static bool TestOverlap(AABB &a, AABB &b){
        float d1x = b.Min.x - a.Max.x;
        float d1y = b.Min.y - a.Max.y;
        float d2x = a.Min.x - b.Max.x;
        float d2y = a.Min.y - b.Max.y;

        if(d1x > 0.0f || d1y > 0.0f){
            return false;
        }

        if(d2x > 0.0f || d2y > 0.0f){
            return false;
        }

        return true;
    }
};

#endif //PHYSICS_ENGINE_AABB_H
