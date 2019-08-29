#include <stdio.h>
#include <assert.h>
#include "../../utils/loso_utils.c"

/*
    Reverse string recursively. 
*/

void ReverseString(char string[])
{
    static uint32 i = 0; // 2
    int len = StringLength(string); // 2

    if (string[i])
    {
        char tmp = string[i];
        string[i] = string[len - 1];
        string[len] = tmp;
        string[len - 1] = '\0'; // 42'0'31
        ++i;
        ReverseString(string);
    }
    else 
    {
        string[i] = string[len + 1];
        for (int32 j = 0; j < len; ++j)
        {
            string[i] = string[len + 1];
        }
         // 42331
        string[i + len] = '\0';

    }
    PrintText(string);
}

int main()
{
    char string[] = "1234";
    ReverseString(string);

    // assert(StringsAreEqual(string, "4321"));
}