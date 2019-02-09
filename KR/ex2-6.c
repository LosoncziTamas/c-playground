#include <stdio.h>
#include <assert.h>

/*  Write a function setbits(x, p, n, y) 
    that returns x with the n bits that 
    begin at position p set to the 
    rightmost n bits of y, leaving the 
    other bits unchanged. */

#define ALL_SET ~0

int setbits(int x, int p, int n, int y)
{
    int nSet = ~(ALL_SET << n);  

    int extractY = (y & nSet) << p; 
    int result = (~(nSet << p) & x) | extractY;

    return result;
}

   /*  0       1       2       3       4       5       6       7 
    "0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111",
       8       9       A       B       C       D       E       F 
    "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"*/

int main()
{
    // x = 11111111 y = 11111000 result = 11000111
    assert(setbits(0xFF, 3, 3, 0xF8) == 0xC7); 

    // x = 11111000 y = 00000111 result = 11111111
    assert(setbits(0xF8, 0, 3, 0x07) == 0xFF); 
}