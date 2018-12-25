#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void* safeMalloc(size_t len) 
{
    void* result = malloc(len);
    if (!result) 
    {
        exit(1);
    }
    return result;
}

void* reallocIntArray(int** ptr, size_t len) 
{
    printf("Address of original: %p \n", *ptr);
    void* result = realloc(*ptr, sizeof(*ptr) * len);
    printf("Address of reallocated: %p \n", result);

    // If there is not enough memory, the old memory block is not freed and null pointer is returned.
    if (!result)
    {
        // The original pointer remains valid.
        free(ptr);
        exit(1);
    }
    return result;
}

int main(void) {

    const size_t arraySize = 16;
    int* array = safeMalloc(sizeof(int) * arraySize);

    for(int i = 0; i < arraySize; ++i) 
    {
        array[i] = i;
        printf("%d", i);
    }
    puts("\n");

    const size_t newSize = 32;
    int* result = reallocIntArray(&array, newSize);

    for(int i = 0; i < newSize; ++i) 
    {
        result[i] = i;
        printf("%d", result[i]);
    }
    puts("\n");
    free(result);

    //TODO: realloc in struct array
}