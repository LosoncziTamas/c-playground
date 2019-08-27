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
        IntegerToString(integer / 10, string);
    }
    else 
    {
       i = 0;
       if (integer < 0) 
       {
           string[i++] = '-';
       }
    }
    string[i++] = '0' +  abs(integer) % 10;
    string[i] = '\0';    
}

int main()
{
    char string[10]; 
    IntegerToString(4678, string);
    assert(StringsAreEqual("4678", string));

    IntegerToString(-123, string);
    assert(StringsAreEqual("-123", string));

    IntegerToString(0, string);
    assert(StringsAreEqual("0", string));
}