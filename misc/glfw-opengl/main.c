#include <stdio.h>
#include <stdlib.h>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

const char* VertexShader = 
"#version 330 core\n\
layout (location = 0) in vec3 aPos; \
 \
void main() \
{ \
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); \
}";

const char* FragmentShader =
"#version 330 core\n\
out vec4 FragColor; \
 \
void main() \
{ \
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); \
} ";

static char InfoLog[128];

void ErrorCallback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void CheckShaderState(GLuint shader, GLFWwindow* window)
{
    int  success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        printf(infoLog);
    }
}

void CheckProgramState(GLuint program, GLFWwindow* window)
{
    int  success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(program, 512, NULL, infoLog);
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        printf(infoLog);
    }
}


int main(void)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(640, 480, "GLFW - OpenGL", NULL, NULL);

    if (window)
    {   
        glfwSetKeyCallback(window, KeyCallback);
        glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);  
        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);

        if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            float vertices[] = {
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                0.0f,  0.5f, 0.0f
            }; 
            
            GLuint vbo;
            glGenBuffers(1, &vbo);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertexShader, 1, &VertexShader, NULL);
            glCompileShader(vertexShader);
            CheckShaderState(vertexShader, window);

            GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragmentShader, 1, &FragmentShader, NULL);
            glCompileShader(fragmentShader);
            CheckShaderState(fragmentShader, window);

            GLuint shaderProgram = glCreateProgram();
            glAttachShader(shaderProgram, vertexShader);
            glAttachShader(shaderProgram, fragmentShader);
            glLinkProgram(shaderProgram);

            glDeleteShader(fragmentShader);
            glDeleteShader(vertexShader);
            CheckProgramState(shaderProgram, window);

            glUseProgram(shaderProgram);

            GLuint vao;
            glGenVertexArrays(1, &vao);
            glBindVertexArray(vao);

            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            // Specifying how to interpret the provided data
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            // Enable vertex attribute at location 0
            glEnableVertexAttribArray(0);

            while (!glfwWindowShouldClose(window))
            {
                glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);

                glBindBuffer(GL_ARRAY_BUFFER, vbo);
                glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
                glEnableVertexAttribArray(0);  

                glUseProgram(shaderProgram);
                glBindVertexArray(vao);
                glDrawArrays(GL_TRIANGLES, 0, 3);

                glfwSwapBuffers(window);
                glfwPollEvents();
            }
        }
        glfwDestroyWindow(window);
    }
}