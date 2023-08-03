
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main()
{
    glfwInit(); // initialization 함수
    // glfwWindowHint을 통해서 GLFW 설정할 수 있음.
    // 첫번째 파라미터는 어떤 옵션을 수정할지
    // 두번째 파라미터는 integer형태로 옵션에 대한 값
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // GLFW_CONTEXT_VERSION_MAJOR와 GLFW_CONTEXT_VERSION_MINOR는 OPENGL이 호환되는 버전을 의미함.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // OpenGL은 3.0 버전이 나오면서 이전의 Fixed Function Pipeline을 사용하지 않기로 합니다. 
    // Fixed Function Pipeline에서 쓰던 glVertex3f, glColor3f 등과 같은 Fixed Function을 
    // 낡은 함수로 취급하고 더 이상 지원하지 않는 것입니다. 
    // GLFW_OPENGL_PROFILE을 GLFW_OPENGL_CORE_PROFILE로 설정한다는 것은 이 낡은 함수들, 즉 하위 호환 함수들을 사용하지 않겠다는 의미입니다.
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if(window == NULL)
    {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    int framebuf_width, framebuf_height;
    glfwGetFramebufferSize(window, &framebuf_width, &framebuf_height);
    glViewport(0, 0, framebuf_width, framebuf_height);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}