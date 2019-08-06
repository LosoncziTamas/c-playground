#include <stdio.h>

/*
    Suppose one character of pushback.
*/

#define INVALID -1

char buf = INVALID;

int getch()
{
    int result;
    if (buf == INVALID)
    {
        result = getchar();
    }
    else
    {
        result = buf;
        buf = INVALID;
    }
    return result;
}

void ungetch(char c)
{
    if (buf == INVALID)
    {
        buf = c;
    }
    else 
    {
        printf("ungetch: too many characters\n");
    }
}