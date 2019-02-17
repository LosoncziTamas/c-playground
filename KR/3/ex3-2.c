#include <stdio.h>

/*  Write a function escape (s, t) 
    that converts characters like 
    newline and tab into visible 
    escape sequences like \n and \t 
    as it copies the string t to s. 
    Use a switch. 
    Write a function for the other 
    direction as well, converting 
    escape sequences into the real 
    characters. */

void escape(char s[], char t[])
{
    int i = 0;
    int offset = 0;

    while(t[i])
    {
        switch (t[i])
        {
            case '\n':
                s[i + offset++] = '\\';
                s[i + offset] = 'n';
                break;
            case '\t':
                s[i + offset++] = '\\';
                s[i + offset] = 't';
                break;
            default:
                s[i + offset] = t[i];
                break;
        }
        ++i;
    }

    s[i + offset + 1] = '\0';
}

void unescape(char s[], char t[])
{
    char prevChar = 0;

    for(int i = 0; t[i]; ++i)
    {
        switch (t[i])
        {
            case 'n':
                if (prevChar == '\\')
                {

                }
                s[i] = '\n';
                break;
            case 't':
                if (prevChar == '\\')
                {

                }
                s[i] = '\t';
                break;
            default:

                break;
        }
        prevChar = t[i];
    }
}

int main()
{
    char s[25] = {0};
    char t[] = "alma \n korte \t barack";
    escape(s, t);
    puts(s);

    return 0;
}