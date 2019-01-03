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
        if (c == ' ' || c == '\t')
        {
            inWord = false;
        }
        else
        {
            if (!inWord || c == '\n')
            {
                putchar('\t');
                for(int i = 0; i < wordLen; ++i)
                {
                    putchar('-');
                }
                putchar('\n');
                wordLen = 0;
            }
            if (c != '\n')
            {
                ++wordLen;
                putchar(c);
            }
            inWord = true;
        }
    }
    return 0;
}