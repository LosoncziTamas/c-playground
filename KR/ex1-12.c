#include <stdio.h>
#include <stdbool.h>

/*  Write a program that prints 
    its input one word per line. */
   
int main(void)
{
    bool blankSkipped = false;
    for (int c = getchar(); c != EOF; c = getchar())
    {
        if (c == '\t' || c == ' ')
        {
            blankSkipped = true;
        }
        else
        {
            if (blankSkipped && c != '\n')
            {
                putchar('\n');   
            }
            putchar(c);
            blankSkipped = false;
        }
    }
    return 0;
}