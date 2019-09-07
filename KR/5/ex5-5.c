#include <stdio.h>
#include "../../utils/loso_utils.c"

/*
    String functions with limits.
*/

char* CopyStringSafe(char* dest, const char* source, uint32 n)
{
    uint32 copyCount = 0;
    char* result = dest;
    
    while (*source && copyCount < n)
    {
        *(dest++) = *(source++);
        copyCount++;
    }
    if (copyCount < 0)
    {
        *dest = '\0';
    }

    return result;
}

char* ConcatStringSafe(char* dest, const char* source, uint32 n)
{
    uint32 copyCount = 0;
    char* result = dest;
    uint32 destLen = StringLength(dest);

    dest += destLen;
    while (*source && copyCount < n)
    {
        *(dest++) = *(source++);
        ++copyCount;    
    }
    *(result + destLen + n) = '\0';
    
    return result;
}

int32 CompareStringSafe(const char* stringA, const char* stringB, uint32 n)
{
    int32 result = 0;
    uint32 compareCount = 0;

    result = *stringA - *stringB;
    while(result == 0 && *stringA && compareCount < n)
    {
        stringA++;
        stringB++;
        result = *stringA - *stringB;
        ++compareCount;
    }

    return result;
}

void TestCopyStringSafe()
{
    char dest[10];
    char* result = CopyStringSafe(dest, "123456789", 1);
    PrintText(result);
    PrintCharArray(result, 10);
}

void TestConcatStringSafe()
{
    char dest[10] = "Concat";
    char* result = ConcatStringSafe(dest, "123456789", 1);
    PrintText(result);
    PrintCharArray(result, 10);
}

void TestCompareStringSafe()
{
    assert(CompareStringSafe("asd", "asd", 5) == 0);
    assert(CompareStringSafe("asd", "asd4", 5) < 0);
    assert(CompareStringSafe("asd4", "asd", 5) > 0);
    //TODO:
    assert(CompareStringSafe("12345AA", "12345BB", 5) == 0);
}

int main()
{
    TestCopyStringSafe();
    TestConcatStringSafe();
    TestCompareStringSafe();
}