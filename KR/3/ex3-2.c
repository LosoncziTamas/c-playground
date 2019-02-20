#include <stdio.h>
#include <stdbool.h>

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
    int offset = 0;
    int i = 0;
    bool escaped = false;

    while(t[i])
    {
        switch (t[i])
        {
            case '\\':
                if (escaped)
                {
                    s[i + --offset] = '\\';
                    s[i + ++offset] = '\\';                    
                    escaped = false;
                }
                else
                {
                    escaped = true;
                }
                break;
            case 'n':
                if (escaped)
                {
                    --offset;
                    s[i + offset] = '\n';
                }
                else
                {
                    s[i + offset] = 'n';
                }
                escaped = false;
                break;
            case 't':
                if (escaped)
                {
                    --offset;
                    s[i + offset] = '\t';
                }
                else
                {
                    s[i + offset] = 't';
                }
                escaped = false;
                break;
            default:
                if (escaped)
                {
                    s[i + --offset] = '\\';
                    ++offset;
                }
                s[i + offset] = t[i];
                escaped = false;
                break;
        }
        ++i;
    }

    s[i + offset + 1] = '\0';
}

int main()
{
    char s[25] = {0};
    char t[] = "alma \n korte \t barack";
    escape(s, t);
    puts(s);

    char s2[23] = {0};
    char t2[] = "alma \\n \\t korte \\t barack";
    unescape(s2, t2);
    puts(s2);
    return 0;
}