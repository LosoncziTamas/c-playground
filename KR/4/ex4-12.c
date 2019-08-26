#include <stdio.h>
#include <math.h>
#include "../../utils/loso_utils.c"

/*
    Write a recursive itoa.
*/

void IntegerToString(int32 integer, char string[])
{
    static int32 i = 0;

    if (integer / 10) 
    {
        i++;
        IntegerToString(integer / 10, string); //4678, 467, 46
    }
    else 
    {
        string[0] = '0' + integer; // 4
        PrintChar(string[0]);
        return;
    }
    string[i--] = '0' + integer / 10; //
}



int main()
{
    char string[10]; 
    IntegerToString(4678, string);
    PrintCharArray(string, 5);
    //assert(StringsAreEqual("4678", string));

    IntegerToString(123, string);
    //assert(StringsAreEqual("123", string));

    //TODO: Fix
    IntegerToString(0, string);
    //assert(StringsAreEqual("0", string));
}