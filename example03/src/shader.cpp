#include "shader.hpp"

#include <vector>


static GLenum ShaderTypeFromString(const std::string& type)
{
    if (type == "vertex")						return GL_VERTEX_SHADER;
    if (type == "fragment" || type == "pixel")	return GL_FRAGMENT_SHADER;

    return 0;
}

Shader::Shader(const std::string& filepath)
{

    std::string shaderSource = ReadFile(filepath);
    auto shaderSources = Preprocess(shaderSource);
    Compile(shaderSources);

    // Extract name from filepath
    auto lastSlash = filepath.find_last_of("/\\");
    lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
    auto lastDot = filepath.rfind('.');
    auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
    m_Name = filepath.substr(lastSlash, count);
}

Shader::~Shader()
{
    glDeleteProgram(m_ID);
}


std::string Shader::ReadFile(const std::string& filepath)
{

    std::string result;
    std::ifstream in(filepath, std::ios::in | std::ios::binary);

    if (in)
    {
        in.seekg(0, std::ios::end);
        result.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&result[0], result.size());
        in.close();
    }
    else
    {
        std::cout << "Could not open file " << filepath << '\n';
    }

    return result;
}

std::unordered_map<GLenum, std::string> Shader::Preprocess(const std::string& source)
{

    std::unordered_map<GLenum, std::string> shaderSources;

    const char* typeToken = "#type";
    size_t typeTokenLength = strlen(typeToken);
    size_t pos = source.find(typeToken, 0);

    while (pos != std::string::npos)
    {
        size_t eol = source.find_first_of("\r\n", pos);
        size_t begin = pos + typeTokenLength + 1;
        std::string type = source.substr(begin, eol - begin);

        size_t nextLinePos = source.find_first_of("\r\n", eol);
        pos = source.find(typeToken, nextLinePos);
        shaderSources[ShaderTypeFromString(type)] = 
            source.substr(nextLinePos, 
                            pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
    }
    return shaderSources;
}

void Shader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
{

    GLuint program = glCreateProgram();
    std::array<GLenum, 2> glShaderIDs;
    int glShaderIDIndex = 0;

    for (auto& kv : shaderSources)
    {
        GLenum type = kv.first;
        const std::string& source = kv.second;
        
        GLuint shader = glCreateShader(type);

        const GLchar* sourceCStr = source.c_str();
        glShaderSource(shader, 1, &sourceCStr, 0);

        glCompileShader(shader);

        GLint isCompiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

            glDeleteShader(shader);

            std::cout << infoLog.data() << '\n';
            std::cout << "Shader compilation failure!\n";
            break;
        }

        glAttachShader(program, shader);
        glShaderIDs[glShaderIDIndex++] = shader;
    }		

    glLinkProgram(program);

    // Note the different functions here: glGetProgram* instead of glGetShader*.
    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

        // We don't need the program anymore.
        glDeleteProgram(program);

        std::cout << infoLog.data() << '\n';
        std::cout << "Shader link failure!\n";

        return;
    }

    m_ID = program;

    for (auto id : glShaderIDs)
        glDetachShader(program, id);
}

void Shader::Bind()
{
    glUseProgram(m_ID);
}

void Shader::Unbind()
{
    glUseProgram(0);
}

void Shader::setBool(const std::string &name, bool v) const
{
}

void Shader::setInt(const std::string &name, int v) const
{
}

void Shader::setFloat(const std::string &name, float v) const
{
}
