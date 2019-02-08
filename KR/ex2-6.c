#include <stdio.h>

/*  Write a function setbits(x, p, n, y) 
    that returns x with the n bits that 
    begin at position p set to the 
    rightmost n bits of y, leaving the 
    other bits unchanged. */

int setbits(int x, int p, int n, int y)
{
    int allSet = ~0;            // 11111111
    int nSet = ~(allSet << n);  // 00000111
    int setFromP = nSet << p;   // 00011100

    int extractY = (y & nSet) << p; // rightmost n bits of y shifted by p
    int result = (x | setFromP) & extractY;

    return result;
}

int main()
{

}