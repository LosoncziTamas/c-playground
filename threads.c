#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* threadFunction(void* arg)
{
    char *message = (char*)arg;
    printf("%s\n", message);

    return NULL;
}

int main()
{
    char* arg = "Hello";
    pthread_t thread;

    if(pthread_create(&thread, NULL, threadFunction, arg)) 
    {
        perror("Error during thread creation");
    }
    // Wait for thread completion.
    pthread_join(thread, NULL);

    return 0;
}