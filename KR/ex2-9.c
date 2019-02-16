#include <assert.h>
#include <stdio.h>

/*  In a two's complement number 
    system, x &= (x-1) deletes 
    the rightmost 1-bit in x. 
    Explain why. Use this observation 
    to write a faster version of bitcount. */

/*  In two's complement system all odd numbers
    have the rightmost set to 1.
    Subtracting one even from a negative number
    will always change the rightmost bit.
    x = x & (x - 1); */

int bitcount(unsigned x)
{
    int count = 0;
    for (count = 0; x; ++count){
        x = x & (x - 1);
    }
    return count;
}

int main()
{
    assert(bitcount(0xFFU) == 8);
    assert(bitcount(0xFU) == 4);
    assert(bitcount(0xC7U) == 5);
    assert(bitcount(0) == 0);
}