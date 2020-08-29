#include <string.h>

char out[1000];

int GetToken();

void ParseDirectDeclarator();

void ParseDeclarator()
{
    int starCount = 0;

    while (GetToken() == '*')
    {
        starCount++;
    }

    ParseDirectDeclarator();

    while (starCount > 0)
    {
        strcat(out, " pointer to");
        starCount--;
    }
}