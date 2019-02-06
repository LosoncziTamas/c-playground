#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/*  Write an alternate version of 
    squeeze (s1, s2) that deletes 
    each character in s1 that matches
    any character in the string s2. */

void squeeze(char* s1, char* s2)
{
    int len = strlen(s1);
    for (int i = 0; s1[i] != '\0'; ++i)
    {
        bool shiftPiece = false;

        for (int j = 0; s2[j] != '\0'; ++j)
        {
            if (s1[i] == s2[j])
            {
                shiftPiece = true;
                break;
            }
        }

        if (shiftPiece)
        {
            for (int pieceIndex = i; pieceIndex < len - 1; ++pieceIndex)
            {
                char tmp = s1[pieceIndex + 1];
                s1[pieceIndex] = tmp;
            }
            s1[len] = '\0';
            --i;
            --len;
        }
    }
}

int main()
{
    char s1[] = "alma korte barack";
    char s2[] = "aeiouaa";
    squeeze(s1, s2);
}