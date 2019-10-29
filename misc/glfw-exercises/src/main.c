#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "utils.h"

// Try to draw 2 triangles next to each other using glDrawArrays by adding more vertices to your data.

typedef GLuint Shader;
typedef GLuint Program;

GLuint SetupVAO()
{
    
}

void FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


Shader CreateShader(GLenum shaderType, const char* source)
{
    Shader result = glCreateShader(shaderType);
    glShaderSource(result, 1, &source, NULL);
    glCompileShader(result);
    return result;
}

Shader CreateShaderProgram(Shader vertex, Shader fragment)
{
    Program program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);
    return program;
}

int main()
{
    if (glfwInit())
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwSwapInterval(1);
        GLFWwindow* window = CreateWindow("Exercise 1");

        if (window && gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);

            const char* vertexShaderSource = ReadTextFile("src/ex1.vert");
            const char* fragmentShaderSource = ReadTextFile("src/ex1.frag");

            if (fragmentShaderSource && vertexShaderSource)
            {
                Shader vertex = CreateShader(GL_VERTEX_SHADER, vertexShaderSource);
                CheckShaderState(vertex, window);
                Shader fragment = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
                CheckShaderState(fragment, window);
                Program program = CreateShaderProgram(vertex, fragment);
                CheckProgramState(program, window);

                glUseProgram(program);

                while (!glfwWindowShouldClose(window))
                {
                    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                    {
                        glfwSetWindowShouldClose(window, GLFW_TRUE);
                    }

                    glClear(GL_COLOR_BUFFER_BIT);
                    glfwSwapBuffers(window);
                    glfwPollEvents();
                }

                glDeleteShader(vertex);
                glDeleteShader(fragment);
            }
            glfwDestroyWindow(window);
        }
    }
}