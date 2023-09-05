//
// Created by apgra on 8/31/2023.
//

#define VERTEX_INDEX 0
#define FRAGMENT_INDEX 0

#include "Shader.h"

#include <glad/glad.h>
#include <sstream>
#include <fstream>
#include <iostream>

#include "glm/gtc/type_ptr.hpp"

Shader::Shader(const char *filePath) {
    m_Handle = createShaderProgram(filePath);
}

unsigned int Shader::createShaderProgram(const char *path) {
    unsigned int shaderProgram;

    shaderProgram = glCreateProgram();
    auto shaders = parseShader(path); //Vertex: 0 Fragment: 1

    glAttachShader(shaderProgram, shaders[0]);
    glAttachShader(shaderProgram, shaders[1]);

    glLinkProgram(shaderProgram);

    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::LINKING_FAILURE\n" << infoLog << "\n";
    }

    //Cleanup
    glDeleteShader(shaders[0]);
    glDeleteShader(shaders[1]);

    return shaderProgram;
}

std::vector<unsigned int> Shader::parseShader(const char *path) {
    std::vector<unsigned int> shaders(2);
    std::ifstream file(path);


    std::string line;
    std::string src;
    int curShader;

    while (std::getline(file, line)) {
        if (line == "#vertex") {
            curShader = VERTEX_INDEX;
            src.clear();
        } else if (line == "#fragment") {
            shaders[curShader] = createShader(src.c_str(), GL_VERTEX_SHADER);
            curShader = FRAGMENT_INDEX;
            src.clear();
        } else {
            src.append(line + "\n");
        }
    }

    //Assumes fragment is final shader
    shaders[curShader] = createShader(src.c_str(), GL_FRAGMENT_SHADER);

    return shaders;
}

unsigned int Shader::createShader(const char *src, unsigned int type) {
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << "ERROR::" << ((type == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT") << "::SHADER::COMPILATION_FAILED\n" << infoLog << "\n";
    }

    return shader;
}

void Shader::bind() const {
    glUseProgram(m_Handle);
}

void Shader::unbind() const {
    glUseProgram(0);
}



int Shader::getUniformLocation(const std::string &name) const {
    if(m_UniformCache.find(name) != m_UniformCache.end()){
        return m_UniformCache[name];
    }

    int location = glGetUniformLocation(m_Handle, name.c_str());
    m_UniformCache[name] = location;

    return location;
}


void Shader::setInt(const std::string &name, int v) {
    glUniform1i(getUniformLocation(name), v);
}

void Shader::setFloat(const std::string &name, float v) {
    glUniform1f(getUniformLocation(name), v);
}

void Shader::setVec2(const std::string &name, glm::vec2 v) {
    glUniform2f(getUniformLocation(name), v.x, v.y);
}

void Shader::setVec2(const std::string &name, float x, float y) {
    glUniform2f(getUniformLocation(name), x, y);
 }

void Shader::setVec3(const std::string &name, glm::vec3 v) {
    glUniform3f(getUniformLocation(name), v.x, v.y, v.z);
}

void Shader::setVec3(const std::string &name, float x, float y, float z) {
    glUniform3f(getUniformLocation(name), x, y, z);
}

void Shader::setVec3(const std::string &name, float v) {
    glUniform3f(getUniformLocation(name), v, v, v);
}

void Shader::setVec4(const std::string& name, glm::vec4 v) {
    glUniform4f(getUniformLocation(name), v.x, v.y, v.z, v.w);
}

void Shader::setVec4(const std::string &name, float x, float y, float z, float w) {
    glUniform4f(getUniformLocation(name), x, y, z, w);
}


void Shader::setMat4(const std::string &name, glm::mat4 v) {
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(v));
}
