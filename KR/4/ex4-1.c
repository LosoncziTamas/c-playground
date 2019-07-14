#include <string.h>
#include <stdio.h>

/*  
    Write the function strrindex(s, t), which returns the position
    of the rightmost occcurence of t in s, or -1 if there is none.
*/  

int strrindex(char s[], char t[]) 
{
    int result = -1;
    int j = 0;
    int tlen = strlen(t);

    for (int i = 0; s[i]; ++i) 
    {
        if (s[i] == t[j]) 
        {
            ++j;
            if (j == tlen)
            {
                result = i - j + 1;
                j = 0;
            }
        }
        else
        {
            j = 0;
        }
    }

    return result;
}

int main(void) 
{
    char* t = "12";
    char* s = "102s1asdasd12asd1";
    int result = strrindex(s, t);
    printf("%d", result);
    return 0;
}