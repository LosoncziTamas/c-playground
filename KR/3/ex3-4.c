#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

/*  In a two's complement number representation, our version of
    itoa does not handle the largest negative number, that is, the value of n equal
    to -(2^wordsize-1). Explain why not. Modify it to print that value correctly,
    regardless of the machine on which it runs. */

/*  There is one extra negative number which doesn't 
    have a corresponding positive. So it cannot be negated. */
 
void reverse(char c[])
{
    int len = strlen(c);
    for (int i = 0; i < (len / 2); ++i)
    {
        char tmp = c[i];
        c[i] = c[len - 1 - i];
        c[len - 1 - i] = tmp;
    }
}

void itoa(int n, char s[])
{
    int i = 0;
    int sign = n;
    do
    {
        s[i++] = abs(n % 10) + '0'; 
    } 
    while ((n /= 10) != 0);
    if (sign < 0)
    {
        s[i++] = '-';
    }
    s[i] = '\0';
    reverse(s);
}

int main()
{
    char str[64];
    itoa(INT_MIN, str);
    puts(str);
}