#include <stdio.h>

/*  Write a program entab that replaces 
    strings of blanks by the minimum 
    number of tabs and blanks to achieve 
    the same spacing. 
    Use the same tab stops as for detab. 
    When either a tab or a single blank 
    would suffice to reach a tab stop, 
    which should be given preference? */

#define TAB_WIDTH 8
#define COLUMN_COUNT 5

int main(void)
{
    for(int c = getchar(), blankCount = 0; c != EOF; c = getchar())
    {
        if (c == ' ')
        {
            blankCount++;
        }
        else if (c == '\t')
        {
            blankCount += TAB_WIDTH;
        }
        else
        {
            if (blankCount != 0)
            {
                int tabCount = blankCount / TAB_WIDTH;
                int spaceCount = blankCount % TAB_WIDTH;
                for (int i = 0; i < tabCount; ++i)
                {
                    putchar('\t');
                }
                for (int i = 0; i < spaceCount; ++i)
                {
                    putchar(' ');
                }
                blankCount = 0;
            } 
            putchar(c);
        }

    }
    return 0;
}