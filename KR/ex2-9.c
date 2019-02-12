#include <stdio.h>

/*  In a two's complement number 
    system, x &= (x-1) deletes 
    the rightmost 1-bit in x. 
    Explain why. Use this observation 
    to write a faster version of bitcount. */

/*
    In two's complement system all odd numbers
    have the rightmost set to 1.
    Subtracting one even from a negative number
    will always change the rightmost bit.
    x = x & (x - 1); 

*/

int bitcount(unsigned x)
{
    x = x & (x - 1);
    return 0;
}

int main()
{

}