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

void printBlanksOptimally(int tabCount, int spaceCount)
{
    /*int tabCount = blankCount / TAB_WIDTH;
    int spaceCount = blankCount % TAB_WIDTH;

    for (int i = 0; i < tabCount; ++i)
    {
        putchar('\t');
    }*/
    // tab at most is TAB_WIDTH long
    for (int i = 0; i < (tabCount * TAB_WIDTH) + spaceCount; ++i)
    {
        putchar(' ');
    }
}

int main(void)
{
    for(int c = getchar(), tabCount = 0, spaceCount = 0, charCount = 0; c != EOF; c = getchar())
    {
        if (c == ' ')
        {
            spaceCount++;
        }
        else if (c == '\t')
        {
            tabCount++;
        }
        else
        {
            if (tabCount + spaceCount > 0)
            {
                printBlanksOptimally(tabCount, spaceCount);
                tabCount = spaceCount = 0;
            } 
            putchar(c);
            charCount++;
        }
    }
    return 0;
}