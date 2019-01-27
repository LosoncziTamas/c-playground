#include <stdio.h>
#include <stdbool.h>
/*
    Write a program to remove all
    comments from a C program. 
    Don't forget to handle quoted
    strings and character constants properly. 
    C comments do not nest.
*/

int main(void)
{
    bool inQuote = false;
    bool inLineComment = false;
    bool inBlockComment = false;
    char lastChar = 0;

    for (int c = getchar(); c != EOF; c = getchar())
    {
        if (c == '"')
        {
            inQuote = !inQuote;
        }

        if (!inQuote && lastChar == '/')
        {
            if (c == '*')
            {
                inBlockComment = true;
            }
            else if (c == '/')
            {
                inLineComment = true;
            }
        }

        if (inLineComment)
        {
            if (c == '\n')
            {
                inLineComment = false;
                lastChar = 0;
                continue;
            }
        }
        else if (inBlockComment)
        {
            if (lastChar == '*' && c == '/')
            {
                inBlockComment = false;
                lastChar = 0;
                continue;
            }
        }
        else 
        {
            if (lastChar != 0)
            {
                putchar(lastChar);
            }
        }
        lastChar = c;
    }
    putchar(lastChar);
    return 0;
}