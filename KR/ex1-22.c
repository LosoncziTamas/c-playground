#include <stdio.h>
#include <stdbool.h>
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

int movePieceToFront(char line[], int start, int end)
{
    int len = end - start;
    for (int i = 0; i < len; ++i)
    {
        line[i] = line[start + i];
        line[start + i] = 0;
    }
    return len;
}

int main(void)
{
    char line[MAX_LENGTH] = {0};
    for (int c = getchar(), charIndex = 0, lastBlankIndex = 0; c != EOF; c = getchar())
    {
        bool isBlank = c == ' ' || c == '\t';
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
                bool skipFirst = charIndex == 0 && isBlank;
                if (skipFirst)
                {
                    charIndex++;
                    continue;
                }
                if (isBlank)
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
            if (isBlank)
            {
                flushLine(line, charIndex);
                charIndex = 0;
                lastBlankIndex = 0;
            } 
            else if (lastBlankIndex != 0)
            {   
                //TODO: fix
                flushLine(line, lastBlankIndex + 1);
                charIndex = movePieceToFront(line, lastBlankIndex + 1, charIndex);
            }
            else
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
            putchar('\n');
        }
    }
    return 0;
}