#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#define MAX_FILE_LEN 512

char* ReadShader(const char* fileName)
{
    char* result = NULL;

    FILE* file = fopen(fileName, "r");
    if (file)
    {
        if (fseek(file, 0, SEEK_END) == 0)
        {
            int elementCount = ftell(file);
            rewind(file);
            if (elementCount > 0 && elementCount < MAX_FILE_LEN)
            {
                //TODO: check why fseek and fread element count is inconsistent on Windows
                char* buffer = calloc(elementCount + 1, 1);
                int readCount = fread(buffer, 1, elementCount, file);
                result = buffer;
#if __APPLE__
                if (readCount == elementCount)
                {
                    result = buffer;
                }
#endif
            }
        }
        fclose(file);
    }

    return result;
}

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
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        int logLen;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);
        char* infoLog = alloca(logLen);
        
        glGetShaderInfoLog(shader, logLen, NULL, infoLog);
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        fprintf(stderr, "Shader compilation error: %s\n", infoLog);
        getchar();
    }
}

void CheckProgramState(GLuint program, GLFWwindow* window)
{
    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        int logLen;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLen);
        char* infoLog = alloca(logLen);

        glGetShaderInfoLog(program, logLen, NULL, infoLog);
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        fprintf(stderr, "Shader linking error: %s\n", infoLog);
        getchar();
    }
}

#define SafeFree(memory) _SafeFree((void*) memory)
void _SafeFree(void* memory)
{
    if (memory)
    {
        free(memory);
    }
}

void DrawTriangle(GLFWwindow* window)
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

    // Creating a VAO that stores the configuration (vertex data, attributes)
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Specifying how to interpret the provided data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // Enable vertex attribute at location 0
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draws using the currently active shader, the defined vertex attribute config and the VBO's data.
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void DrawRectangle(GLFWwindow *window)
{
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    float vertices[] =
    {
        - 0.5f, - 0.5f, 0.0f,   // 0: bottom left
          0.5f, - 0.5f, 0.0f,   // 1: bottom right
          0.5f,   0.5f, 0.0f,   // 2: top right
        - 0.5f,   0.5f, 0.0f    // 3: top left
    };

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint indices[] =
    {
        2, 1, 3,
        1, 0, 3
    };

    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
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

        const char* vertexShaderSource = ReadShader("src/main.vert");
        const char* fragmentShaderSource = ReadShader("src/main.frag");

        if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) && vertexShaderSource && fragmentShaderSource)
        {   
            // Enabling alpha blending
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

            GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
            // TODO: why did it crash before?
            glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
            glCompileShader(vertexShader);
            CheckShaderState(vertexShader, window);

            GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
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

            DrawRectangle(window);

            glDeleteProgram(shaderProgram);
        }

        SafeFree(fragmentShaderSource);
        SafeFree(vertexShaderSource);
        glfwDestroyWindow(window);
    }
}