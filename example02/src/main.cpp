
#include <iostream>
#include <fstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

std::string ReadFile(const char* filePath)
{
    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);

    while (!fileStream.is_open())
    {
            printf("Failed to read %s file! The file doesn't exist.\n", filePath);
            return "";
    }

    std::string line = "";
    while (!fileStream.eof())
    {
            std::getline(fileStream, line);
            content.append(line + "\n");
    }

    fileStream.close();
    return content;
}

GLuint AddShader(const char* shaderCode, GLenum shaderType)
{
    GLuint new_shader = glCreateShader(shaderType);

    const GLchar* code[1];
    code[0] = shaderCode;

    glShaderSource(new_shader, 1, code, NULL);

    GLint result = 0;
    GLchar err_log[1024] = { 0 };

    glCompileShader(new_shader);
    glGetShaderiv(new_shader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
            glGetShaderInfoLog(new_shader, sizeof(err_log), NULL, err_log);
            printf("Error compiling the %d shader: '%s'\n", shaderType, err_log);
            return 0;
    }
    return new_shader;
}

GLuint CompileShader(const char* vsCode, const char* fsCode)
{
    GLuint vs, fs;

    GLuint shader = glCreateProgram();

    if (!shader)
    {
            printf("Error: Cannot create shader program.");
            return 0;
    }

    vs = AddShader(vsCode, GL_VERTEX_SHADER);
    fs = AddShader(fsCode, GL_FRAGMENT_SHADER);
    glAttachShader(shader, vs);  // Attach shaders to the program for linking process.
    glAttachShader(shader, fs);

    GLint result = 0;
    GLchar err_log[1024] = { 0 };

    glLinkProgram(shader);  // Create executables from shader codes to run on corresponding processors.
    glGetProgramiv(shader, GL_LINK_STATUS, &result);
    if (!result)
    {
            glGetProgramInfoLog(shader, sizeof(err_log), NULL, err_log);
            printf("Error linking program: '%s'\n", err_log);
            return 0;
    }

    return shader;
}

GLuint CreateShaderProgramFromFiles(const char* vsPath, const char* fsPath)
{
    std::string vsFile = ReadFile(vsPath);
    std::string fsFile = ReadFile(fsPath);
    const char* vsCode = vsFile.c_str();
    const char* fsCode = fsFile.c_str();

    return CompileShader(vsCode, fsCode);
}

GLFWwindow* init_create_window()
{    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if(window == NULL)
    {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }

    int framebuf_width, framebuf_height;
    glfwGetFramebufferSize(window, &framebuf_width, &framebuf_height);
    glViewport(0, 0, framebuf_width, framebuf_height);

    return window;
}

int main()
{
    GLFWwindow* window = init_create_window();
    if(!window)
    {
        return -1;
    }

    // Define vertice spec
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
    };

    GLuint VAO;
    GLuint VBO;

    glGenVertexArrays(1, &VAO); // VAO 생성
    glBindVertexArray(VAO); // VAO를 OpenGL context에 연결(bind)

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    GLuint shader = CreateShaderProgramFromFiles("../shader/shader.vert", "../shader/shader.frag");

    while (!glfwWindowShouldClose(window))
    {
                glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);

                glUseProgram(shader);

                glBindVertexArray(VAO);
                glDrawArrays(GL_TRIANGLES, 0, 3);
                glBindVertexArray(0);

                glUseProgram(0);

                glfwSwapBuffers(window);
                glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}