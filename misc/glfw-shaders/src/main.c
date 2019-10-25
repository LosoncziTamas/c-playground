#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define ArraySize(x) (sizeof(x) / sizeof(x[0]))

#define MEM_SIZE 2048

typedef struct 
{
    char buffer[MEM_SIZE];
    unsigned int buffP;
} Memory;

Memory* AllocateMemory()
{
    Memory *result = calloc(1, sizeof(Memory));
    result->buffP = 0;
    return result;
}

void FreeMemory(Memory* memory)
{
    if (memory)
    {
        free((void*)memory);
    }
}

char* GetMemory(Memory* memory, unsigned int size)
{
    char* result = 0;

    if (ArraySize(memory->buffer) < memory->buffP + size)
    {
        // TODO: Quit with failure.
        exit(1);
    }
    else
    {
        result = memory->buffer + memory->buffP;
        memory->buffP += size; 
    }

    return result;
}

typedef enum
{
    SUCCESS = 1,
    FILE_ERROR = 2,
    READ_ERROR = 3
} ReadState;

typedef struct 
{
    char* data;
    unsigned int length;
} TextFileContent;

void PrintWarning(const char* text)
{
    fprintf(stderr, "Warning: %s\n", text);
}

ReadState ReadTextFile(const char* fileName, Memory* memory, TextFileContent* out)
{
    FILE *file = fopen(fileName, "r");
    if (!file)
    {
        return FILE_ERROR;
    }

    if (fseek(file, 0, SEEK_END))
    {
        fclose(file);
        return READ_ERROR;
    }

    int elementCount = ftell(file);
    rewind(file);

    out->data = GetMemory(memory, elementCount + 1);
    out->length = fread(out->data, 1, elementCount, file);
    // Element count can be different from read count: CRLF vs. CR line feed. Use LF so files are translated properly.
    if (out->length != elementCount)
    {
        PrintWarning("Inconsistent read count.");
    }
    
    fclose(file);

    return SUCCESS;
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

GLFWwindow* CreateWindow(const char* title)
{
    GLFWwindow* result = glfwCreateWindow(800, 600, title, NULL, NULL);

    if (result)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
        glfwSetKeyCallback(result, KeyCallback);
        glfwSetFramebufferSizeCallback(result, FrameBufferSizeCallback);  
        glfwMakeContextCurrent(result);
        glfwSwapInterval(1);
    }

    return result;
}

void SetupTriangle()
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
}

// TODO: unify state checks

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

int main()
{
    Memory* appMemory = AllocateMemory();

    if (glfwInit())
    {
        GLFWwindow* window = CreateWindow("Shaders");
        if (window)
        {
            if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                TextFileContent vertexShaderSource = {0};
                TextFileContent fragmentShaderSource = {0};

                if (ReadTextFile("src/main.vert", appMemory, &vertexShaderSource) == SUCCESS &&
                    ReadTextFile("src/main.frag", appMemory, &fragmentShaderSource) == SUCCESS)
                {
                    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
                    glShaderSource(fragmentShader, 1, &fragmentShaderSource.data, NULL);
                    glCompileShader(fragmentShader);
                    CheckShaderState(fragmentShader, window);

                    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
                    glShaderSource(vertexShader, 1, &vertexShaderSource.data, NULL);
                    glCompileShader(vertexShader);
                    CheckShaderState(vertexShader, window);

                    GLuint program = glCreateProgram();
                    glAttachShader(program, fragmentShader);
                    glAttachShader(program, vertexShader);
                    glLinkProgram(program);
                    glDeleteShader(fragmentShader);
                    glDeleteShader(vertexShader);
                    CheckProgramState(program, window);

                    glUseProgram(program);

                    SetupTriangle();

                    GLint vertexColorLocation = glGetUniformLocation(program, "ourColor");
                    if (vertexColorLocation == -1)
                    {
                        glfwSetWindowShouldClose(window, GLFW_TRUE);
                    }

                    while(!glfwWindowShouldClose(window))
                    {
                        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                        glClear(GL_COLOR_BUFFER_BIT);
                        
                        float t = glfwGetTime();
                        float green = (sinf(t) / 2.0f) + 0.5f;
                        glUniform4f(vertexColorLocation, 0.0f, green, 0.0f, 1.0f);

                        glDrawArrays(GL_TRIANGLES, 0, 3);
                        
                        glfwSwapBuffers(window);
                        glfwPollEvents();
                    }

                    // TODO: delete VAO and VBO
                }
            }
            glfwDestroyWindow(window);
        }
        glfwTerminate();
    }

    FreeMemory(appMemory);

    return 0;
}