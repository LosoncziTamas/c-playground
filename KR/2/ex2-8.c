#include <assert.h>

/*  Write a function rightrot(x,n) 
    that returns the value of the 
    integer x rotated to the right
    by n bit positions. */

unsigned int rightrot(unsigned int x, unsigned int n)
{
    n = n % 32;
    unsigned int captureMask = ~((~0U) >> n);
    unsigned int result = (x >> n) | captureMask;

    return result;
}

int main()
{
    assert(rightrot(0xFF, 3) == 0xE000001F);
}