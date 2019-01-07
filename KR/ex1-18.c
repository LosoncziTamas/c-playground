#include <stdio.h>

/*  Write a program to remove 
    trailing blanks and tabs 
    from each line of input, 
    and to delete entirely 
    blank lines. */

int main(void)
{
    int spaceCount = 0;
    int tabCount = 0;

    for(int c = getchar(); c != EOF; c = getchar())
    {
        if (c == ' ')
        {
            spaceCount++;
        }
        else if (c == '\t')
        {
            tabCount++;
        }
        else if (c == '\n')
        {
            putchar(c);
            spaceCount = tabCount = 0;
        } 
        else 
        {
            for (int i = 0; i < spaceCount; ++i)
            {
                putchar(' ');
            }
            for (int i = 0; i < tabCount; ++i)
            {
                putchar('\t');
            }
            putchar(c);
            spaceCount = tabCount = 0;
        }
    }

    return 0;
}