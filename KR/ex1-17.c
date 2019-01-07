#include <stdio.h>
#include <stdbool.h>

#define MIN 80

/*  Write a program to print all
    input lines that are longer 
    than 80 characters. */

int main(void)
{
    char buffer[MIN];
    int bufferIndex = 0;
    bool overMin = false;

    for (int c = getchar(); c != EOF; c = getchar())
    {
        if (c != '\n')
        {
            if (bufferIndex < MIN - 1)
            {
                buffer[bufferIndex] = c;
                ++bufferIndex;
            }
            else
            {
                if (!overMin)
                {
                    buffer[MIN - 1] = '\0';
                    printf("%s", buffer);
                    overMin = true;
                }
                putchar(c);
            }
        }
        else
        {
            if (overMin)
            {
                putchar(c);
            }
            bufferIndex = 0;
            overMin = false;
        }
    }
    return 0;
}