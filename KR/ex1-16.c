#include <stdio.h>
#include <stdbool.h>

#define MAXLINE 5 

/*  Revise the main routine of
    the longest-line program 
    so it will correctly print
    the length of arbitrarily
    long input lines, and as
    much as possible of the text. */


int getLine(char line[], int maxline)
{
    int i, c;
    for(i = 0, c = getchar(); c != EOF && c != '\n'; c = getchar())
    {
        // end of line, buffer is not full
        if (c == '\n' && i < maxline)
        {
            line[i] = '\n';
            line[i + 1] = '\0';
        } 
        // end of line, buffer is full
        else if (c == '\n' && i >= maxline)
        {
            line[maxline - 1] = '\n';
            line[maxline] = '\0';
        }
        else if (i < maxline)
        {
            line[i] = c;
        }
        ++i;
    }
    return i;
}

void copy(char to[], char from[])
{
    for(int i = 0; (to[i] = from[i]) != '\0'; ++i);
}

int main(void)
{
    char line[MAXLINE];
    char longest[MAXLINE];
    int max = 0;
    int len = 0;
    while((len = getLine(line, MAXLINE)) > 0)
    {
        if (len > max)
        {
            max = len;
            copy(longest, line);
        }
    }
    printf("length: %d %s", len, longest);
    return 0;
}