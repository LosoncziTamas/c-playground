#include <stdio.h>

/*  Write a program to print a 
    histogram of the frequencies
    of different characters in 
    its input. */                              

int main(void)
{
    //TODO: non-ascii support
    int charCount[128] = {0};
    for (int c = getchar(); c != EOF; c = getchar())
    {
        charCount[c]++; 
    }
    for (int i = 0; i < 128; ++i)
    {
        if (charCount[i] != 0)
        {
            printf("%c\t", i);
            for (int j = 0; j < charCount[i]; ++j)
            {
                putchar('-');
            }
            putchar('\n');
        }
    }
    return 0;
}