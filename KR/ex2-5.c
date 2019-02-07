#include <stdio.h>

/*  Write the function any (s1, s2), 
    which returns the first location
    in the string s1 where any 
    character from the string s2 
    occurs, or -1 if s1 contains 
    no characters from s2. 
    (The standard library function
    strpbrk does the same job but 
    returns a pointer to the location.) */

int any(const char* s1, const char* s2)
{
    for (int i = 0; s1[i]; ++i)
    {
        for (int j = 0; s2[j]; ++j)
        {
            if (s1[i] == s2[j])
            {
                return i;
            }
        }
    }
    return -1;
}

int main()
{
    char s1[] = "Hello, world!";
    char s2[] = "lord";
    int result = any(s1, s2);
    if (result == -1)
    {
        puts("No occurence found.");
    }
    else
    {
        printf("First location at: %d.", result);
    }
}