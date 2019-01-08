#include <stdio.h>

/*
    Write a program detab that replaces tabs in the input
    with the proper number of blanks to space to the next
    tab stop. Assume a fixed set of tab stops, say every 
    n columns. Should n be a variable or a symbolic 
    parameter? */

#define TAB_WIDTH 8

int main()
{
    int tabStops = 5;
    
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
    }

    return 0;
}