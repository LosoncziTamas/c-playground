#include <stdio.h>
#include <limits.h>
#include <float.h>

/*
    Write a program to determine 
    the ranges of char, short, 
    int, and long variables, both
    signed and unsigned, by printing
    appropriate values from standard
    headers and by direct computation.
    Harder if you compute them: 
    determine the ranges of the 
    various floating-point types.
*/

void printSizes()
{
    // signed char
    printf("signed char min: %d ", SCHAR_MIN);
    printf("signed char max: %d\n", SCHAR_MAX);

    // unsigned char
    printf("unsigned char min: %u ", 0);
    printf("signed char max: %u\n", UCHAR_MAX);

    // signed short
    printf("signed short min: %d ", SHRT_MIN);
    printf("signed short max: %d\n", SHRT_MAX);

    // unsigned short
    printf("unsigned short min: %u ", 0);
    printf("unsigned short max: %u\n", USHRT_MAX);

    // signed long
    printf("signed long min: %ld ", LONG_MIN);
    printf("signed long max: %ld\n", LONG_MAX);

    // unsigned long
    printf("unsigned long min: %ld ", 0L);
    printf("unsigned long max: %lu\n", ULONG_MAX);
}

void computeSizes()
{
    // signed char
    int charSize = sizeof(char) * 8;
    char minSignedChar = 1 << (charSize - 1);
    char maxSignedChar = ~(1 << (charSize - 1));

    printf("signed char min: %d ", minSignedChar);
    printf("signed char max: %d\n", maxSignedChar);

    // unsigned char
    unsigned char maxUnsignedChar = ~0;

    printf("unsigned char min: %u ", 0);
    printf("unsigned char max: %u\n", maxUnsignedChar);

    // signed short
    int shortSize = sizeof(short) * 8;
    short minSignedShort = 1 << (shortSize - 1);
    short maxSignedShort = ~(1 << (shortSize - 1));

    printf("signed short min: %d ", minSignedShort);
    printf("signed short max: %d\n", maxSignedShort);

    // unsigned short
    unsigned short maxUnsignedShort = ~0;

    printf("unsigned short min: %d ", 0);
    printf("unsigned short max: %d\n", maxUnsignedShort);

    // signed long
    int longSize = sizeof(long) * 8;
    long minSignedLong = (1L << (longSize - 1));
    long maxSignedLong = ~(1L << (longSize - 1));

    printf("signed long min: %ld ", minSignedLong);
    printf("signed long max: %ld\n", maxSignedLong);

    // unsigned long
    unsigned long maxUnsignedLong = ~0;

    printf("unsigned long min: %lu ", 0L);
    printf("unsigned long max: %lu\n", maxUnsignedLong);
}

int main()
{
    printSizes();
    putchar('\n');
    computeSizes();
    putchar('\n');

    printf("float min: %.10e ", FLT_MIN);
    printf("float max: %.10e\n", FLT_MAX);

    printf("double min: %.10e ", DBL_MIN);
    printf("double max: %.10e\n", DBL_MAX);

    printf("long double min: %.Le ", LDBL_MIN);
    printf("long double max: %.Le\n", LDBL_MAX);

    return 0;
}