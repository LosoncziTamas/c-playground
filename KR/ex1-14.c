#include <stdio.h>

/*  Write a program to print a 
    histogram of the frequencies
    of different characters in 
    its input. */                              

int main(void)
{
    int charCount[256] = {0};
    for (int c = getchar(); c != EOF; c = getchar())
    {
        char asChar = c;
        printf("%c ", asChar);
        charCount[asChar]++; 
        printf("%d \n", charCount[asChar]);

    }
    for (int i = 0; i < 256; ++i)
    {
        char asChar = i;
        if (charCount[asChar] != 0)
        {
            printf("%c\t", asChar);
            for (int j = 0; j < charCount[asChar]; ++j)
            {
                putchar('-');
            }
            putchar('\n');
        }
    }
    return 0;
}