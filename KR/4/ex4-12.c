#include <stdio.h>
#include <math.h>
#include "../../utils/loso_utils.c"

/*
    Write a recursive itoa.
*/

void IntegerToString(int32 integer, char string[])
{
    if (integer == 0)
    {
        *string = '0' + integer;
    }
    else
    {
        int32 tmp = integer; //1234
        int32 base = 10;
        uint32 magnitude = 0;

        while (tmp = tmp / base) //0
        {
            magnitude++; //3
        }
        int32 exponent = pow(10.0, magnitude);
        *string = '0' + integer / exponent;
        IntegerToString(integer % exponent, ++string); 
    }
}

int main()
{
    char string[5];
    IntegerToString(1234, string);
}