#include <stdio.h>

#define BUFSIZE 100

static int buf[BUFSIZE];
static int bufp = 0;

int getch()
{
    int val = bufp > 0 ? buf[--bufp] : getchar();
    return val;
}

void ungetch(int c)
{
    if (bufp < BUFSIZE)
    {
        buf[bufp++] = c;
    }
    else 
    {
        printf("ungetch: too many characters\n");
    }
}