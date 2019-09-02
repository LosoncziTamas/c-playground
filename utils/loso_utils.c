#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define ArrayCount(array) (sizeof(array)) / (sizeof((array)[0]))

typedef uint32_t uint32;
typedef int32_t int32;
typedef int32 bool32;

#define BUFSIZE 100

static int buf[BUFSIZE];
static int bufp = 0;

int32 GetChar()
{
    int32 val = bufp > 0 ? buf[--bufp] : getchar();
    return val;
}

void UngetChar(int32 c)
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

void PrintInteger(int32 integer)
{
    printf("%d\n", integer);
}

void PrintText(const char* text)
{
    printf("%s\n", text);
}

void PrintChar(char c)
{
    printf("%c\n", c);
}

uint32 StringLength(const char* string)
{
    uint32 result = 0;

    for(uint32 charIndex = 0; string[charIndex]; ++charIndex)
    {
        ++result;
    }

    return result;
}

uint32 StringLengthSafe(const char* string, uint32 max)
{
    uint32 result = 0;

    for(uint32 charIndex = 0; string[charIndex] && charIndex < max; ++charIndex)
    {
        ++result;
    }

    return result;
}

void StringConcat(const char* sourceA, uint32 sourceALen, const char* sourceB, uint32 sourceBLen, char* dest, uint32 destLen)
{
    assert(destLen > sourceALen + sourceBLen);

    for(uint32 charIndex = 0; charIndex < sourceALen; ++charIndex)
    {
        dest[charIndex] = sourceA[charIndex];
    }
    for(uint32 charIndex = 0; charIndex < sourceBLen; ++charIndex)
    {
        dest[sourceALen + charIndex] = sourceB[charIndex];
    }
    dest[sourceALen + sourceBLen] = '\0';
}

bool StringsAreEqual(const char* stringA, const char* stringB)
{
    uint32 charIndex;

    for(charIndex = 0; stringA[charIndex]; ++charIndex)
    {
        if(stringA[charIndex] != stringB[charIndex])
        {
            return false;
        }
    }

    return stringA[charIndex] == stringB[charIndex];
}


void PrintIntegerArray(int32* array, uint32 count)
{
    printf("[");
    for (uint32 elementIndex = 0; elementIndex < count; ++elementIndex)
    {
        if (elementIndex == count - 1)
        {
            printf("%d]\n", array[elementIndex]);
        }
        else 
        {
            printf("%d, ", array[elementIndex]);
        }
    }
}

void PrintCharArray(char* array, uint32 count)
{
    printf("[");
    for (uint32 elementIndex = 0; elementIndex < count; ++elementIndex)
    {
        if (elementIndex == count - 1)
        {
            printf("%c]\n", array[elementIndex]);
        }
        else 
        {
            printf("%c, ", array[elementIndex]);
        }
    }
}

