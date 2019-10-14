#include <stdio.h>

// Arrays are converted to pointers, and you cannot determine the size of the array from a pointer
// I guess that's why the main function also passes the argc parameter
void attemptToPrintArraySize(int *arr)
{
    // The size of a pointer on a 64 bit computer is 8 bytes (8 x 8 = 64)
    printf("sizeof(arr) %lu", sizeof(arr));
    printf("\n");

    // The size of the value pointed by the pointer
    printf("sizeof(arr[0]) %lu", sizeof(arr[0]));
    printf("\n");

    size_t size = sizeof(arr) / sizeof(arr[0]);
    printf("sizeof(arr) / sizeof(arr[0]) %lu", size);
    printf("\n");
}

typedef struct
{
    int arr[10];
} Array;

// Wrapping the array in a struct could be a fix for this
// So you either put the static array into a struct or you provide the size to the consumer function
void printArraySize(Array *arr)
{
    size_t size = sizeof(arr->arr) / sizeof(arr->arr[0]);
    printf("sizeof(arr->arr) / sizeof(arr->arr[0]) %lu", size);
    printf("\n");
}

void printArrayContent(int *arr, size_t size)
{
    for (int i = 0; i < size; ++i)
    {
        printf("index: %d content: %d", i, arr[i]);
        printf("\n");
    }
}

int main(void)
{
    // Set all elements to 0, otherwise the content is garbage
    int arr[10] = {0};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    attemptToPrintArraySize(arr);

    printArrayContent(arr, size);

    Array arr2;
    printArraySize(&arr2);

    return 0;
}
