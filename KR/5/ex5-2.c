#include <stdio.h>
#include <ctype.h>
#include "../../utils/loso_utils.c"

int GetFloat(float* fp)
{
    int32 c;
    while (isspace(c = GetChar()));
    if (!isdigit(c) && c != EOF && c != '+' && c != '-')
    {
        UngetChar(c);
        return 0;
    }

    int32 sign = c == '-' ? -1 : 1;
    float i = 1.0f;
    *fp = 0.0f;
    while (isdigit(c))
    {
        *fp *= i;
        *fp += c - '0';
        i = 10.0f;
        c = GetChar();
    }
    // TODO: Fix
    if (c == '.')
    {
        c = GetChar();
        i = 0.1f;
        while (isdigit(c))
        {
            *fp += (c - '0') * i;
            i *= 0.1f;
        }
    }
    *fp *= sign;
    if ( c != EOF)
    {
        UngetChar(c);
    }
    return c;
}

int main()
{
    int32 status;
    float f;
    while ((status = GetFloat(&f)) != EOF)
    {
        if (status > 0)
        {
            PrintText("Valid number.");
        }
        else 
        {
            PrintText("Not a number.");
            break;
        }
        printf("%f \n", f);
    }
}