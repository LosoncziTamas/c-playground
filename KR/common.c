#include <stdio.h>

#include "common.h"

#define BUFSIZE 100

static int buf[BUFSIZE];
static int bufp = 0;

static Stream activeStream = 
{
    .type = Console,
    .datap = 0,
    .data = {0}
};

void SetStream(Stream* stream)
{
    activeStream = *stream;
}

int GetChar()
{
    if (bufp > 0)
    {
        return buf[--bufp];
    }

    if (activeStream.type == Memory)
    {
        int datap = activeStream.datap;
        if (datap < ArrayCount(activeStream.data))
        {
            int result = activeStream.data[datap];
            activeStream.datap++;
            return result;
        }
    }
    else if (activeStream.type == Console)
    {
        return getchar();
    }

    return -1;
}

void UngetChar(int c)
{
    if (bufp < BUFSIZE)
    {
        buf[bufp++] = c;
    }
    else 
    {
        printf("UngetChar: too many characters.\n");
    }
}