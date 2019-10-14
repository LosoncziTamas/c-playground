#include <stdio.h>
#include <stdlib.h>
#include <alloca.h>

size_t returnArrayLength() 
{
    return 42;
}

void printArray(int* array, size_t len) 
{
    for(int i = 0; i < len; ++i) 
    {
        printf("%d: %d \t", i, array[i]);
        if (i % 10 == 0) 
        {
            printf("\n");
        }
    }
}

int main(void) 
{
    size_t len = returnArrayLength();
    // The memory is allocated on stack and not freed until the function returns.
    int* stackAllocated = alloca(sizeof(int) * len);
    printArray(stackAllocated, len);

    // Allocate and sets mem to zeros
    int* heapAllocated = calloc(sizeof(int), len);
    if (heapAllocated) {
        printArray(heapAllocated, len);
        free(heapAllocated);
    }

    return 0;
}