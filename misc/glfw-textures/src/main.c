#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>

#include "utils.h"

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

int main()
{
    if (glfwInit())
    {
        GLFWwindow *window = CreateWindow("Textures");
        glfwSetKeyCallback(window, KeyCallback);
        glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);

        if (window && gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            GLuint vao;
            glGenVertexArrays(1, &vao);
            glBindVertexArray(vao);

            float vertices[] = 
            {
                -0.5f, -0.5f, 0.0f, // bottom-left 
                 0.5f, -0.5f, 0.0f, // bottom-right
                 0.5f,  0.5f, 0.0f, // top-right
                -0.5f,  0.5f, 0.0f  // top-left
            };

            GLuint vbo;
            glGenBuffers(1, &vbo);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            GLuint indices[] =
            {
                0, 1, 2,
                0, 2, 3
            };

            GLuint ebo;
            glGenBuffers(1, &ebo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            const char* fragmentShaderSrc = ReadTextFile("src/main.frag");
            const char* vertexShaderSrc = ReadTextFile("src/main.vert");

            if (fragmentShaderSrc && vertexShaderSrc)
            {
                GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
                glShaderSource(vShader, 1, &vertexShaderSrc, NULL);
                glCompileShader(vShader);
                CheckShaderState(vShader, window);

                GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
                glShaderSource(fShader, 1, &fragmentShaderSrc, NULL);
                glCompileShader(fShader);
                CheckShaderState(fShader, window);

                GLuint program = glCreateProgram();
                glAttachShader(program, vShader);
                glAttachShader(program, fShader);
                glLinkProgram(program);
                CheckProgramState(program, window);
                glDeleteShader(vShader);
                glDeleteShader(fShader);
                glUseProgram(program);

                while (!glfwWindowShouldClose(window))
                {
                    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                    glClear(GL_COLOR_BUFFER_BIT);

                    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

                    glfwSwapBuffers(window);
                    glfwPollEvents();
                }

                glDeleteProgram(program);
                glDeleteVertexArrays(1, &vao);
                glDeleteBuffers(1, &vbo);
                glDeleteBuffers(1, &ebo);
                free((void*)vertexShaderSrc);
                free((void*)fragmentShaderSrc);
            }
        }
        glfwDestroyWindow(window);
    }

    return 0;
}