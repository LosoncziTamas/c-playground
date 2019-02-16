#include <stdio.h>

/*  Write a loop equivalent to 
    the for loop above without
    using && or ||. */

void oldLoop()
{
    int i;
    int lim = 10;
    int c;
    for (i = 0; i < lim - 1 && (c = getchar()) != '\n' && c != EOF; ++i)
    {
        putchar(c);
    }
}

int main(void)
{
    int lim = 10;
    for (int i = 0, c = getchar(); i < lim - 1; ++i, c = getchar())
    {
        if (c == '\n')
        {
            break;
        }
        if (c == EOF)
        {
            break;
        }
        putchar(c);
    }
    return 0;
}