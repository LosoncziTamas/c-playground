#include <stdio.h>

/*  In a two's complement number 
    system, x &= (x-1) deletes 
    the rightmost 1-bit in x. 
    Explain why. Use this observation 
    to write a faster version of bitcount. */

/*  The rightmost 1-bit of x has a 
    corresponding 0-bit in x - 1. Masking
    will always clear the rightmost bit of x. */

int bitcount(unsigned x)
{
    x = x & (x - 1);
    return 0;
}

int main()
{

}