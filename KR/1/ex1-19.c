#include <stdio.h>

/*  Write a function reverse(s)
    that reverses the character
    string s. Use it to write a
    program that reverses its
    input a line at a time. */

#define MAX_LINE 1024

void reverse(char string[], int len)
{
    char tmp;
    for (int i = 0; i < len / 2; ++i)
    {
        tmp = string[i];
        string[i] = string[len - i - 1];
        string[len - i - 1] = tmp;
    }
}

int main(void)
{
    char line[MAX_LINE] = {0};

    for(int c = getchar(), i = 0; c != EOF; c = getchar())
    {
        if (i < MAX_LINE)
        {
            if (c == '\n')
            {
                line[i] = '\0';
                reverse(line, i);
                printf("%s %d\n", line, i);
                i = 0;
            }
            else
            {
                line[i] = c;
                ++i;
            }
        }
        else
        {
            printf("Line too long, max %d chars are allowed.\n", MAX_LINE - 1);
            i = 0;
        }
    }

    return 0;
}