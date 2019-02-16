#include <stdio.h>
#include <stdbool.h>

#define MAXLINE 1000

/*  Revise the main routine of
    the longest-line program 
    so it will correctly print
    the length of arbitrarily
    long input lines, and as
    much as possible of the text. */

int getLine(char line[], int maxline)
{
    int storedIndex, realIndex, c;
    bool overflow = false;

    for(storedIndex = 0, realIndex = 0, c = getchar(); c != EOF && c != '\n'; c = getchar())
    {
        if (storedIndex < maxline - 1)
        {
            line[storedIndex] = c;
            ++storedIndex;
        } 
        else
        {
            overflow = true;
        }
        ++realIndex;
    }
    if (overflow)
    {
        line[maxline - 2] = '\n';
        line[maxline - 1] = '\0';
        ++realIndex;
    } 
    else if (c == '\n')
    {
        line[storedIndex] = '\n';
        line[storedIndex + 1] = '\0';
        ++realIndex;
    }
    return realIndex;
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
    printf("length: %d %s", max, longest);
    return 0;
}