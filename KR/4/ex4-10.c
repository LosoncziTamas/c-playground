#include <stdio.h>

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getline(char s[], int lim) 
{
    int c, i;

    i = 0;
    while(--lim > 0 && (c = getchar()) != EOF && c != '\n')
    {
        s[i++] = c;
    }
    if (c == '\n')
    {
        s[i++] = c;
    }
    s[i] = '\0';
    return i;
}

int getop(char s[])
{
    char c;
    if (bufp == 0 || buf[bufp] == '\0')
    {
        bufp = 0;
        // clear buffer
        getline(buf, BUFSIZE);
    }
    
    while((c = buf[bufp++]) == ' ' || c == '\t')
        ;
    // if (isdigit())
}