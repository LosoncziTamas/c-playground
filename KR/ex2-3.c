#include <stdio.h>

/*  Write the function htoi(s), 
    which converts a string of 
    hexadecimal digits (including an 
    optional 0x or 0X) into its 
    equivalent integer value. The 
    allowable digits are 0 through 9, 
    a through f, and A through F. */

int htoi(char s[])
{
    int result = 0;
    for (int i = 0; s[i + 2] != '\0'; ++i)
    {
        char c = s[i + 2];
        int val = 0;
        if (c >= 'A' && c <= 'F')
        {
            val = c - 55; 
        }
        else if (c >= 'a' && c <= 'f')
        {
            val = c - 87; 
        }
        else if (c >= '0' && c <= '9')
        {
            val = c - '0'; 
        }
        else 
        {
            return 0;
        }
        result = 16 * result + val; 
    }
    return result;
}

int main(void)
{
    char* s = "0x10"; 
    char* s2 = "0xFF"; 
    htoi(s);
    htoi(s2);
    return 0;
}