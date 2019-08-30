#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "../../utils/loso_utils.c"

/*
    Reverse string recursively. 
*/

int32 CeilFloatToInt32(float real)
{
    int32 result = (int32)ceilf(real);
    return result;
}

void ReverseString(char string[])
{
    static int32 i = 0;
    uint32 len = StringLength(string);
    PrintInteger(i);
    if (i == (len / 2))
    {
        
        i = 0;
        return;
    }
    uint32 swapIndexA = (len / 2) - i - 1;
    uint32 swapIndexB = CeilFloatToInt32(len / 2.0f) + i;
    char tmp = string[swapIndexA];
    printf("swapping: %c %c \n", string[swapIndexA], string[swapIndexB]);
    string[swapIndexA] = string[swapIndexB];
    string[swapIndexB] = tmp;
    ++i; 
    ReverseString(string);
}

void TestReverse1()
{
    char string[] = "1234";
    ReverseString(string);
    assert(StringsAreEqual(string, "4321"));
}

void TestReverse2()
{
    char string[] = "123";
    ReverseString(string);
    PrintText(string);
    assert(StringsAreEqual(string, "321"));
}

void TestReverse3()
{
    char string[] = "12";
    ReverseString(string);
    assert(StringsAreEqual(string, "21"));
}

void TestReverse4()
{
    char string[] = "1";
    ReverseString(string);
    assert(StringsAreEqual(string, "1"));
}

int main()
{
    TestReverse1();
    TestReverse2();
    TestReverse3();
    TestReverse4();
}