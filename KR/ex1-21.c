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
 

void printBlanksOptimally(int blankCount, int charCount)
{
    /*int tabCount = blankCount / TAB_WIDTH;
    int spaceCount = blankCount % TAB_WIDTH;

    for (int i = 0; i < tabCount; ++i)
    {
        putchar('\t');
    }*/
    // tab at most is TAB_WIDTH long
    for (int i = 0; i < blankCount; ++i)
    {
        putchar(' ');
    }
}

int main(void)
{
    for(int c = getchar(), blankCount = 0, charCount = 0; c != EOF; c = getchar())
    {
        if (c == ' ')
        {
            blankCount++;
        }
        else if (c == '\t')
        {
            int nextStop = TAB_WIDTH - ((charCount + blankCount) % TAB_WIDTH);
            blankCount += nextStop;
            //printf("\n charCount %d blankCount %d \n", charCount, blankCount);
        }
        else
        {
            if (blankCount > 0)
            {
                printBlanksOptimally(blankCount, charCount);
                charCount += blankCount;
                blankCount = 0;
            }
            charCount = c == '\n' ? 0 : charCount + 1;
            putchar(c);
        }
    }
    return 0;
}