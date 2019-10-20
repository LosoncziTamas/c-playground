#include <stdio.h>
#include "GLFW/glfw3.h"

void ErrorCallback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

int main(void)
{
    GLFWwindow* window;

    if (glfwInit())
    {
        glfwSetErrorCallback(ErrorCallback);
        GLFWwindow* window = glfwCreateWindow(640, 480, "GLFW", NULL, NULL);
        
        if (window)
        {
            glfwMakeContextCurrent(window);

            while (!glfwWindowShouldClose(window))
            {
                glClear(GL_COLOR_BUFFER_BIT);
                glfwSwapBuffers(window);
                glfwPollEvents();

                if (glfwGetKey(window, GLFW_KEY_ESCAPE))
                {
                    glfwSetWindowShouldClose(window, GLFW_TRUE);
                }
            }
        }
        glfwTerminate();
    }
}