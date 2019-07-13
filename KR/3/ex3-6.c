#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*  
    Write a version of itoa that accepts three arguments instead of
    two. The third argument is a minimum field width; the converted number must
    be padded with blanks on the left if necessary to make it wide enough.
*/

void reverse(char str[], int len) 
{
    for (int i = 0; i < len / 2; ++i) 
    {
        char tmp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = tmp;
    }
}

void itoa(int n, char str[], int minWidth) 
{
    int sign = 0;
    int i = 0;
    int counter = 0;

    while (n) 
    {
        int frac = abs(n % 10);
        n = n / 10;
        str[i++] = '0' + frac;
        counter++;
    }
    if (sign < 0) 
    {
        str[i++] = '-';
        ++counter;
    }
    for (int j = 0; j < minWidth - counter; ++j)
    {
        str[i++] = ' ';
    }
    reverse(str, i);
}

int main (void) 
{
    char str[32];
    itoa(125, str, 5);
    printf("%s", str);
    return 0;
}


