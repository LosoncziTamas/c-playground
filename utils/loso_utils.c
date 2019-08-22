#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define ArrayCount(array) (sizeof(array)) / (sizeof((array)[0]))

void TestArrayCount()
{
    int array[100]; 
    assert(ArrayCount(array) == 100);

    struct Foo 
    {
        char a;
        char b;
    };
    struct Foo fooArray[50];
    assert(ArrayCount(fooArray) == 50);

    struct Bar
    {
        int a[20];
    };
    struct Bar bar;
    assert(ArrayCount(bar.a) == 20);
}

typedef uint32_t uint32;
typedef int32_t int32;
typedef int32 bool32;

void TestIntSize()
{
    assert(sizeof(uint32) == 4);
    assert(sizeof(int32) == 4);
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

void TestStringLength()
{
    assert(StringLength("1234") == 4);
    assert(StringLength("") == 0);

    char string[100];
    uint32 max = 32;
    assert(StringLengthSafe(string, max) < max);
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

void TestStringsAreEqual()
{
    assert(StringsAreEqual("1 2 ", "1 2 "));
    assert(StringsAreEqual(" 1 2 ", " 1 2 "));
    assert(!StringsAreEqual("1 2 ", " 1 2  "));
    assert(!StringsAreEqual("  1 2 ", " 1 2"));
}

void TestStringConcat()
{
    char sourceA[] = "1234";
    char sourceB[] = "5678";
    char dest[10];

    StringConcat(sourceA, 4, sourceB, 4, dest, 10);
    assert(StringsAreEqual("12345678", dest));
}

int main(void) 
{
    TestArrayCount();
    TestIntSize();
    TestStringLength();
    TestStringConcat();
    TestStringsAreEqual();
}