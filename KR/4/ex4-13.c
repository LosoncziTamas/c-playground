#include <stdio.h>
#include <assert.h>
#include "../../utils/loso_utils.c"

/*
    Reverse string recursively. 
*/

void ReverseString(char string[])
{
    static uint32 i = 0;
    if (string[i])
    {
        ++i;
        ReverseString(string);
    }
    PrintInteger(i);
}

int main()
{
    char string[] = "1234";
    ReverseString(string);

    assert(StringsAreEqual(string, "4321"));
}