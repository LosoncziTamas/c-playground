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

void printBlanksOptimally(int blankCount, int charPerLine)
{
    int toNextStop = TAB_WIDTH - ((charPerLine - blankCount) % TAB_WIDTH);
    
    // move to next tab stop
    if (blankCount >= toNextStop)
    {
        putchar('\t');
        blankCount -= toNextStop;
    }

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
}

int main(void)
{
    for(int c = getchar(), blankCount = 0, charPerLine = 0; c != EOF; c = getchar())
    {
        if (c == ' ')
        {
            blankCount++;
            charPerLine++;
        }
        else if (c == '\t')
        {
            int toNextStop = TAB_WIDTH - (charPerLine % TAB_WIDTH);
            blankCount += toNextStop;
            charPerLine += toNextStop;
        }
        else
        {
            if (blankCount > 0)
            {
                printBlanksOptimally(blankCount, charPerLine);
                blankCount = 0;
            }
            putchar(c);
            charPerLine = c == '\n' ? 0 : charPerLine + 1;
        }
    }
    return 0;
}