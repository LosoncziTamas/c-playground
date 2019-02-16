#include <stdio.h>

/*  Rewrite the function lower, 
    which converts upper case letters
    to lower case, with a conditional
    expression instead of if-else. */

void lower(char str[]) 
{
    for(int i = 0; str[i]; ++i)
    {
        char c = str[i];
        str[i] = c >= 'A' && c <= 'Z' ? c + 'a' - 'A' : c;
    }
}

int main()
{
    char str[] = "Ablak Zsiraf";
    lower(str);
    puts(str);
}