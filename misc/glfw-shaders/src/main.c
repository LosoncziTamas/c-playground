#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

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
                    while(!glfwWindowShouldClose(window))
                    {
                        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                        glClear(GL_COLOR_BUFFER_BIT);

                        glfwSwapBuffers(window);
                        glfwPollEvents();
                    }
                }
            }
            glfwDestroyWindow(window);
        }
        glfwTerminate();
    }

    FreeMemory(appMemory);

    return 0;
}