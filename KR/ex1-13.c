#include <stdio.h>
#include <stdbool.h>

/*  Write a program to print a histogram of
    the lengths of words in its input. It
    is easy to draw the histogram with the
    bars horizontal; a vertical orientation
    is more challenging. */

int main(void)
{
    bool inWord = true;
    int wordLen = 0;
    for (int c = getchar(); c != EOF; c = getchar())
    {
        if (c == ' ' || c == '\t' || c == '\n')
        {
            inWord = false;
        }
        else
        {
            if (!inWord)
            {
                printf("\t%d\n", wordLen);
                wordLen = 0;
            }
            putchar(c);
            ++wordLen;
            inWord = true;
        }
    }
    return 0;
}