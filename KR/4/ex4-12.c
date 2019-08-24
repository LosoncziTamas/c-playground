#include <stdio.h>
#include <math.h>
#include "../../utils/loso_utils.c"

/*
    Write a recursive itoa.
*/

void IntegerToString(int32 integer, char string[])
{
    if (integer < 0)
    {
        *string = '-';
        string = &string[1];
        //TODO: How to handle -INT_MIN
        IntegerToString(-integer, string);
        return;
    }
    if (integer == 0)
    {
        *string = '\0';
    }
    else
    {
        int32 tmp = integer;
        int32 base = 10;
        uint32 magnitude = 0;

        while (tmp = tmp / base)
        {
            magnitude++;
        }
        int32 exponent = pow(10.0, magnitude);
        *string = '0' + integer / exponent;
        string = &string[1];
        IntegerToString(integer % exponent, string); 
    }
}

int main()
{
    char string[10]; 
    IntegerToString(4678, string);
    assert(StringsAreEqual("4678", string));

    IntegerToString(-123, string);
    assert(StringsAreEqual("-123", string));

    //TODO: Fix
    IntegerToString(0, string);
    assert(StringsAreEqual("0", string));
}