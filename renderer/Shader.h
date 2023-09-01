//
// Created by apgra on 8/31/2023.
//

#ifndef PHYSICS_ENGINE_SHADER_H
#define PHYSICS_ENGINE_SHADER_H


#include <vector>

class Shader {
private:
    unsigned int m_Handle;


public:
    Shader(const char* filePath);


    void bind() const;
    void unbind() const;


private:
    static unsigned int createShaderProgram(const char* path);
    //Vert Shader: Index 0  Frag Shader: Index 1
    static std::vector<unsigned int> parseShader(const char* path);
    static unsigned int createShader(const char* src, unsigned int type);


public:
    //Uniforms
};


#endif //PHYSICS_ENGINE_SHADER_H
