#include <stdio.h>
#include <stdlib.h>

void modifyArray(int* array, size_t count) 
{
    for(int i = 0; i < count; ++i)
    {
        array[i]++;
        printf("%d ", array[i]);
    }
    printf("\n");
}

void printArray(int* array, size_t count) 
{
    for(int i = 0; i < count; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void assignToArray(int** array, size_t count)
{
    int* tmp = malloc(sizeof(*array) * count);
    for(int i = 0; i < 5; ++i) 
    {
        tmp[i] = 5;
    }
    free(*array);
    *array = tmp;
    printf("\n");
}

int main(void) 
{
    int *array = malloc(sizeof(*array) * 5); 
    size_t count = 5;
    printf("Total array size: %zu \n", sizeof(*array) * 5);
    printArray(array, count);
    modifyArray(array, count);
    printArray(array, count);
    assignToArray(&array, count);
    printArray(array, count);
    free(array);
    return 0;
}
