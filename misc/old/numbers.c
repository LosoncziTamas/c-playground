#include <stdio.h>

typedef char sint8;
typedef short sint16;
typedef int sint32;
typedef long sint64;

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long uint64;

typedef float f32;
typedef double f64;

void printNumberSizes() {
    printf("sizeof(sint8) %lu", sizeof(sint8));    
    printf("\n");

    printf("sizeof(sint16) %lu", sizeof(sint16));
    printf("\n");

    printf("sizeof(sint32) %lu", sizeof(sint32));
    printf("\n");

    printf("sizeof(sint64) %lu", sizeof(sint64));
    printf("\n");

    printf("sizeof(f32) %lu", sizeof(f32));
    printf("\n"); 

    printf("sizeof(f64) %lu", sizeof(f64));    
    printf("\n");
}

typedef union {
    f32 real;
    uint32 integer;
} Float;

void playingWithFloat() {
    Float f;
    f.real = 1.0f;

    printf("%f", f.real);
    printf("\n");
    printf("%u", f.integer);
    printf("\n");

    f.integer >>= 1;

    printf("%f", f.real);
    printf("\n");
    printf("%u", f.integer);
    printf("\n");
}

int main(int argc, char const *argv[])
{
    printNumberSizes();
    playingWithFloat();

    return 0;
}
