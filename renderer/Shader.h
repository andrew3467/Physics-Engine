//
// Created by apgra on 8/31/2023.
//

#ifndef PHYSICS_ENGINE_SHADER_H
#define PHYSICS_ENGINE_SHADER_H


#include <vector>
#include <unordered_map>
#include <string>

#include <glm/glm.hpp>

class Shader {
private:
    unsigned int m_Handle;

    mutable std::unordered_map<std::string, int> m_UniformCache;

public:
    Shader(const char* filePath);


    void bind() const;
    void unbind() const;


private:
    static unsigned int createShaderProgram(const char* path);
    //Vert Shader: Index 0  Frag Shader: Index 1
    static std::vector<unsigned int> parseShader(const char* path);
    static unsigned int createShader(const char* src, unsigned int type);


    int getUniformLocation(const std::string &name) const;


public:
    //Uniforms
    void setInt(const std::string& name, int v);

    void setFloat(const std::string& name, float v);

    void setVec2(const std::string& name, glm::vec2 v);
    void setVec2(const std::string& name, float x, float y);

    void setVec3(const std::string& name, glm::vec3 v);
    void setVec3(const std::string& name, float x, float y, float z);
    void setVec3(const std::string &name, float v);

    void setVec4(const std::string& name, glm::vec4 v);
    void setVec4(const std::string& name, float x, float y, float z, float w);

    void setMat4(const std::string& name, glm::mat4 v);
};


#endif //PHYSICS_ENGINE_SHADER_H
