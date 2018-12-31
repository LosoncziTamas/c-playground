#include <stdio.h>

/* Count blanks, tabs, and newlines. */

int main(void)
{
    int n = 0;
    for(int c = getchar(); c != EOF; c = getchar())
    {
        if (c == ' ' || c == '\t' || c == '\n')
        {
            ++n;
        }
    }
    printf("Total blanks/tabs/new lines: %d", n);
    return 0;
}