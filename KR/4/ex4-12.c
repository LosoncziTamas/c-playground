#include <stdio.h>
#include <math.h>
#include "../../utils/loso_utils.c"

/*
    Write a recursive itoa.
*/

void IntegerToString(int32 integer, char string[])
{
    PrintInteger(integer);
    PrintCharArray(string, 4);
    if (integer == 0)
    {
        *string = '0' + integer;
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
    char string[5] = {'a', 'b', 'c', 'd', '\0'};
    IntegerToString(1234, string);
    PrintCharArray(string, 4);
}