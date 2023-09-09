#pragma once

#include <glad/glad.h> // include glad to get the required OpenGL headers

#include <cstring>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>

class Shader
{
public:
    Shader(const std::string& filepath);
    ~Shader();

    void Bind();
    void Unbind();
    
    void setBool(const std::string &name, bool v) const;
    void setInt(const std::string &name, int v) const;
    void setFloat(const std::string &name, float v) const;

private:
    std::string ReadFile(const std::string& filepath);
    std::unordered_map<GLenum, std::string> Preprocess(const std::string& source);
    void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);

public:
    uint32_t m_ID;    
    std::string m_Name;
};