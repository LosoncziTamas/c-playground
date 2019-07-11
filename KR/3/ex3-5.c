#include <stdio.h>
#include <string.h>

/*
    Write a function itob(n, s, b) that converts integer n into a base b character
    representation in the string s. In particular, itob(n, s, 16) formats n as a
    hexadecimal integer in s.
*/

void reverse(char str[]) 
{
    int len = strlen(str);
    for (int i = 0; i < len / 2; ++i) {
        char tmp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = tmp;
    }
}

void itob(int n, char s[], int b) 
{
    int i = 0;
    while (n) 
    {
        int frac = n % b;
        n = n / b;
        s[i++] = '0' + frac;
    }
    s[i] = '\0';
    reverse(s);
}

int main(void) 
{
    char str[8];
    itob(1073, str, 16);
    //TODO print in proper format
    puts(str);
    return 0;
}