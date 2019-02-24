#include <string.h>
#include <stdio.h>

/*  In a two's complement number representation, our version of
    itoa does not handle the largest negative number, that is, the value of n equal
    to -(2 ^wordsize-l). Explain why not. Modify it to print that value correctly,
    regardless of the machine on which it runs. */

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

}

int main()
{
    char str[] = "almafa";
    reverse(str);
    puts(str);
}