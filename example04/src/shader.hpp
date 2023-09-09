#pragma once

#include <glad/glad.h> // include glad to get the required OpenGL headers

#include <cstring>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <glm/glm.hpp>

class Shader
{
public:
    Shader(const std::string& filepath);
    ~Shader();

    void Bind();
    void UnBind();
    
    void SetBool(const std::string &name, bool v) ;
    void SetInt(const std::string &name, int v) ;
    void SetFloat(const std::string &name, float v) ;
    void SetMat4(const std::string &name, const glm::mat4& matrix);

private:
    std::string ReadFile(const std::string& filepath);
    std::unordered_map<GLenum, std::string> Preprocess(const std::string& source);
    void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);

public:
    uint32_t m_ID;    
    std::string m_Name;
};