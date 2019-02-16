#include <stdio.h>
#include <stdbool.h>

/*  Write a program to copy its input to its output, 
    replacing each string of one or more blanks by 
    a single blank.*/
    
bool isBlank(int c)
{
    return c == ' ' ||c == '\t';
}

int main(void)
{
    int blankCount = 0;
    for (int c = getchar(); c != EOF; c = getchar())
    {
        if (isBlank(c))
        {
            ++blankCount;   
        }
        else
        {
            if (blankCount > 0)
            {
                putchar(' ');
            }
            putchar(c);
            blankCount = 0;
        }
    }
    return 0;
}