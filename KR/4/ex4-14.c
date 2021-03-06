#include <stdio.h>
#include <assert.h>

/*
    Define swap macro.
*/

#define Swap(t, x, y) {t tmp = (x); (x) = (y); (y) = tmp;}

int main()
{
    int x = 5;
    int y = 6;
    Swap(int, x, y);
    assert(y == 5 && x == 6);

    int* a = &x;
    int* b = &y;
    Swap(int*, a, b);
    assert(*a == 5 && *b == 6);
}