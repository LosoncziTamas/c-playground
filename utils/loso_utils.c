#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint32_t uint32;
typedef int32_t int32;

void TestIntSize()
{
    assert(sizeof(uint32) == 4);
    assert(sizeof(int32) == 4);
}

uint32 StringLength(char* string)
{
    uint32 result = 0;

    for(uint32 charIndex = 0; string[charIndex]; ++charIndex)
    {
        ++result;
    }

    return result;
}

uint32 StringLengthSafe(char* string, uint32 max)
{
    uint32 result = 0;

    for(uint32 charIndex = 0; string[charIndex] && charIndex < max; ++charIndex)
    {
        ++result;
    }

    return result;
}

void TestStringLength()
{
    assert(StringLength("1234") == 4);
    assert(StringLength("") == 0);

    char string[100];
    uint32 max = 32;
    assert(StringLengthSafe(string, max) < max);
}

int main(void) 
{
    TestIntSize();
    TestStringLength();
}