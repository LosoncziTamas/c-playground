#include <stdio.h>
#include <assert.h>

/*  Write a function setbits(x, p, n, y) 
    that returns x with the n bits that 
    begin at position p set to the 
    rightmost n bits of y, leaving the 
    other bits unchanged. */

int setbits(int x, int p, int n, int y)
{
    int allSet = ~0;            // 11111111
    int nSet = ~(allSet << n);  // 00000111
    int setFromP = nSet << p;   // 00111000

    int extractY = (y & nSet) << p; 
    int result = (~setFromP & x) | extractY;

    return result;
}

int main()
{
    // x = 11111111 y = 11111000 result = 11000111
    assert(setbits(0xFF, 3, 3, 0xF8) == 0xC7); 
}