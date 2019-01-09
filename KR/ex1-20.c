#include <stdio.h>

/*
    Write a program detab that replaces tabs in the input
    with the proper number of blanks to space to the next
    tab stop. Assume a fixed set of tab stops, say every 
    n columns. Should n be a variable or a symbolic 
    parameter? */

#define TAB_WIDTH 8
#define COLUMN_COUNT 5

int main()
{    
    for (int c = getchar(), charCount = 0; c != EOF; c = getchar())
    {
        if (c == '\t')
        {
            int space = TAB_WIDTH - (charCount % TAB_WIDTH);
            for(int i = 0; i < space; ++i)
            {
                putchar(' ');
                ++charCount;
            }
        }
        else
        {
            putchar(c);
            ++charCount;
        }
        if (charCount >= COLUMN_COUNT * TAB_WIDTH)
        {
            putchar('\n');
            charCount = 0;
        }
    }

    return 0;
}