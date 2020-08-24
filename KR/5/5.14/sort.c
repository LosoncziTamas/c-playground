#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define MAXLEN 1000

char* Alloc(int size)
{
    assert(size >= 0);
    char* result = (char*) malloc(size);
    return result;
}

int GetLine(char* dest, int max)
{
    assert(dest);
    const char* start = dest;

    for (int c = getchar(); c != EOF && c != '\n' && max > 0; c = getchar())
    {
        --max;
        *(dest++) = c;
    }
    *dest = '\0';

    return dest - start;
}

int ReadLines(char* linePtr[], int maxLines)
{
    char line[MAXLEN];
    int lineCount = 0;

    for (int len = GetLine(line, MAXLEN); len > 0; len = GetLine(line, MAXLEN))
    {
        char* p = Alloc(len);
        if (lineCount >= maxLines || p == NULL)
        {
            return -1;
        }
        else
        {
            line[len] = '\0';
            strcpy(p, line);
            linePtr[lineCount++] = p;
        }
    }

    return lineCount;
}

#define MAXLINES 5000

char* lines[MAXLINES];

int main(int argc, char* argv[])
{
    bool isNumeric = argc > 1 && strcmp(argv[1], "-n") == 0;
    int lineCount = ReadLines(lines, MAXLINES);

    for (int i = 0; i < lineCount; ++i)
    {
        printf("lines[%d] %s \n", i, lines[i]);
    }

    return 0;
}