#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100
#define MAXOP 100
#define NUMBER '0'

char buf[BUFSIZE];
int bufp = 0;

int getline(char s[], int lim) 
{
    int c, i;

    i = 0;
    while(--lim > 0 && (c = getchar()) != EOF && c != '\n')
    {
        s[i++] = c;
    }
    if (c == '\n')
    {
        s[i++] = c;
    }
    s[i] = '\0';
    return i;
}

int getop(char s[])
{
    int c;
    if (bufp == 0 || buf[bufp] == '\0')
    {
        bufp = 0;
        // clear buffer
        getline(buf, BUFSIZE);
    }
    
    while((c = buf[bufp++]) == ' ' || c == '\t')
        ;
    
    if (!isdigit(c) && c != '.') {
        return c;
    }
    int i = 0;
    if (isdigit(c)) {
        while(isdigit(s[i++] = c = buf[bufp++]));
    }
    if (c == '.') {
        while(isdigit(s[i++] = c = buf[bufp++]));
    }
    s[i] = '\0';
    
    return NUMBER;
}

int main()
{
    int type;
    char s[MAXOP];
    
    while((type = getop(s)) != EOF) {
        switch(type) {
            case NUMBER:
            default:
                printf("\n %d", type);
        }
    }
}