//
// Created by apgra on 8/31/2023.
//

#include "Shader.h"

#include <glad/glad.h>
#include <sstream>

Shader::Shader(const char *filePath) {
    m_Handle = createShaderProgram(filePath);
}

unsigned int Shader::createShaderProgram(const char *path) {
    unsigned int shader;

    shader = glCreateProgram();
    auto shaderSrc = parseShader(path);



    return shader;
}

std::vector<unsigned int> Shader::parseShader(const char *path) {
    std::vector<unsigned int> shaders(2);
    std::stringstream ss;




    return shaders;
}

unsigned int Shader::createShader(const char *src, unsigned int type) {
    unsigned int shader = glCreateShader(type);
}
