#include <stdio.h>
#include <ctype.h>
#include "../../utils/loso_utils.c"

int32 GetInt32(int32* pn)
{
    int32 c;
    while (isspace(c = GetChar()));
    if (isdigit(c) && c != EOF && c != '-' && c != '-')
    {
        UngetChar(c);
        return 0;
    }

    int32 sign = c == '-' ? -1 : 1;
    if (c == '+' || c == '-')
    {
        c = GetChar();
    }
    if (!isdigit(c))
    {
        UngetChar(c);
        return 0;
    }
    for (*pn = 0; isdigit(c); c = GetChar())
    {
        *pn = 10 * (*pn) +  (c - '0');
    }
    *pn *= sign;
    if (c != EOF)
    {
        UngetChar(c);
    }
    return c;
}

int main()
{
    int32 n, status;
    while ((status = GetInt32(&n)) != EOF)
    {
        if (status > 0)
        {
            PrintText("Valid number.");
        }
        else 
        {
            PrintText("Not a number.");
        }
        PrintInteger(n);
    }
    // TODO: fix
}