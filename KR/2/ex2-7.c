#include <assert.h>

/*  Write a function invert(x,p,n) 
    that returns x with the n bits 
    that begin at position p inverted
    (i.e., 1 changed into 0 and vice versa),
    leaving the others unchanged. */

#define ALL_SET ~0U

unsigned int invert(unsigned int x, int p, int n)
{
    unsigned int mask = (~(ALL_SET << n)) << p;          
    unsigned int invertedValues = mask & (~(mask & x));

    return (x & (~mask)) | invertedValues;
}

int main()
{
    // x = 11111111 result = 11000111
    assert(invert(0xFF, 3, 3) == 0xC7);

    // x = 00000000 result = 00000011
    assert(invert(0x0, 0, 2) == 0x03);

    // x = 10101010 result = 01010101
    assert(invert(0xAA, 0, 8) == 0x55);
}