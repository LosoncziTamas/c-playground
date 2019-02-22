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
    int j = 0;

    for(int i = 0; s1[i]; ++i)
    {
        if (s1[i] == '-')
        {
            char start = i > 0 ? s1[i - 1] : FIRST;
            char end = s1[i + 1] ? s1[i + 1] : LAST;

            for(int c = start + 1; c < end; ++c)
            {
                s2[j++] = c;
            }
        }
        else
        {
            s2[j++] = s1[i];
        }
    }

    s2[j] = '\0';
}

int main()
{
    char s1[] = "A-Z0-9";
    char s2[100];
    expand(s1, s2);
    printf("%s", s2);
}