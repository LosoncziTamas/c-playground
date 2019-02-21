#include <stdio.h>

/*  Write a function expand (s1, s2) that expands shorthand notations
    like a-z in the string s1 into the equivalent complete list abc... xyz in
    s2. Allow for letters of either case and digits, and be prepared to handle cases
    like a-b-c and a-zO-9 and -a-z. Arrange that a leading or trailing - is
    taken literally. */

#define FIRST 0
#define LAST 127

void expand(char s1[], char s2[])
{
    char start = 0;
    char end = 0;

    for(int i = 0; s1[i]; ++i)
    {
        if (s1[i] == '-')
        {
            start = i > 0 ? s1[i - 1] : FIRST;
            end = s1[i + 1] ? s1[i + 1] : LAST;

            for(char j = start + 1; j < end; ++j)
            {
                putchar(j);
            }
        }
        else
        {
            putchar(s1[i]);
        }
    }
}

int main()
{
    char s1[] = "ab-z";
    char s2[100];
    expand(s1, s2);
}