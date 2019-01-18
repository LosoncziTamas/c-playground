#include <stdio.h>
#include <string.h>

/*  Write a program to "fold" long input lines
    into two or more shorter lines after the 
    last non-blank character that occurs before
    the n-th column of input. Make sure your 
    program does something intelligent with 
    very long lines, and if there are no blanks
     or tabs before the specified column. */

// read til EOF
// count & store chars in array (n-sized)
// keep track of last blank & check limit
// if limit is over then print until the last blank (excluding it), print new line & move the remainder, update variables
// if limit is not over and new line, then print the array and clear variables
// if there are no blanks and limits is over, then split

#define MAX_LENGTH 5

void flushLine(char line[], int charIndex)
{
    for (int i = 0; i < charIndex; ++i)
    {
        putchar(line[i]);
        line[i] = 0;
    }
}

int main(void)
{
    char line[MAX_LENGTH] = {0};
    for (int c = getchar(), charIndex = 0, lastBlankIndex = 0; c != EOF; c = getchar())
    {
        if (charIndex < MAX_LENGTH - 1)
        {
            if (c == '\n')
            {
                flushLine(line, charIndex);
                putchar(c);
                charIndex = 0;
            }
            else
            {
                //TODO: fix
                if (c == ' ' || c == '\t')
                {
                    // tab takes more space, fix later
                    lastBlankIndex = charIndex;
                }
                line[charIndex] = c;
                charIndex++;
            }
        }
        else
        {
            if (lastBlankIndex == 0)
            {   
                flushLine(line, charIndex);
                putchar(c);
                // not terminated
                if (c != '\n')
                {
                    putchar('-');
                }
                charIndex = 0;
            }
            else
            {
                flushLine(line, lastBlankIndex);
                //copy remainder
                int remainderLen = charIndex - lastBlankIndex;
                for (int i = 0; i < remainderLen; ++i)
                {
                    line[i] = line[charIndex + i];
                    line[charIndex + i] = 0;
                }
                charIndex = remainderLen - 1;
            }
            putchar('\n');
        }
    }
    return 0;
}