#include <stdio.h>

void copyInput()
{
    int c;
    while ((c = getchar()) != EOF)
    {
        putchar(c);
    }
}

int main(void)
{
    int result = getchar() == EOF;
    printf("getchar is %d \n", result);
    return 0;
}