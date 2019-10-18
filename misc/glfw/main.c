#include <stdio.h>
#include "GLFW/glfw3.h"

typedef struct 
{
    int leftButtonPressed;
    int rightButtonPressed;
    int upButtonPressed;
    int downButtonPressed;
    int escButtonPressed;
} Input;

typedef struct
{
    Input input;
} AppState;

void ErrorCallback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

Input ReadInput(GLFWwindow* window)
{
    Input result = {};

    result.leftButtonPressed = glfwGetKey(window, GLFW_KEY_LEFT);
    result.rightButtonPressed = glfwGetKey(window, GLFW_KEY_RIGHT);
    result.downButtonPressed = glfwGetKey(window, GLFW_KEY_DOWN);
    result.upButtonPressed = glfwGetKey(window, GLFW_KEY_UP);
    result.escButtonPressed = glfwGetKey(window, GLFW_KEY_ESCAPE);

    return result;
}

int main(void)
{
    GLFWwindow* window;

    if (glfwInit())
    {
        glfwSetErrorCallback(ErrorCallback);
        
        GLFWwindow* window = glfwCreateWindow(640, 480, "GLFW", NULL, NULL);
        AppState state = {0};

        if (window)
        {
            glfwMakeContextCurrent(window);

            while (!glfwWindowShouldClose(window))
            {
                glClear(GL_COLOR_BUFFER_BIT);
                glfwSwapBuffers(window);
                glfwPollEvents();

                state.input = ReadInput(window);
                if (state.input.escButtonPressed)
                {
                    glfwSetWindowShouldClose(window, GLFW_TRUE);
                }
            }
        }
        glfwTerminate();
    }
}