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

#define MAX_LENGTH 5

void flushLine(char line[], int size)
{
    for (int i = 0; i < size; ++i)
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
            } 
            else if (lastBlankIndex != 0)
            {   
                flushLine(line, lastBlankIndex + 1);
                int pieceLen = movePieceToFront(line, lastBlankIndex + 1, charIndex);
                line[pieceLen] = c;
                charIndex = pieceLen + 1;
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
            lastBlankIndex = 0;
            putchar('\n');
        }
    }
    return 0;
}