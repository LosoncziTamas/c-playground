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
        if (c >= 'A' && c <= 'F')
        {
            
        }
        else if (c >= 'a' && c <= 'f')
        {
            

        }
        else if (c >= '1' && c <= '9')
        {
            
        }
        else if (c == '0')
        {
            
        }
        else 
        {
            return 0;
        }
    }
    return result;
}

int main(void)
{
    char* s = "0x10"; // 16
    char* s2 = "0xFF"; // 255
    htoi(s);
    return 0;
}