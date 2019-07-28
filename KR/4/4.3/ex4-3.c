#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "io.c"
#include "stack.c"

#define NUMBER '0'
#define MAXOP 100

int getop(char s[])
{
    int i, c;
    while((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    // not a number
    if (!isdigit(c) && c != '.')
    {
        return c;
    } 
    i = 0;
    // collect integer
    if (isdigit(c))
    {
        while (isdigit(s[++i] = c = getch()))    
            ;
    }
    // collect fraction
    if (c == '.')
    {
        while (isdigit(s[++i] = c = getch()))
            ;
    }
    s[i] = '\0';
    if (c != EOF){
        ungetch(c);
    }
    
    return NUMBER;
}

int main()
{
    int type;
    double op2;
    char s[MAXOP];

    while((type = getop(s)) != EOF) 
    {
        printf("type %d \n", type);
        switch (type)
        {
            case NUMBER:
                push(atof(s));
                break;
            case '+':(
                push(pop() + pop()));
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '*':
                push(pop() * pop());
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0) 
                {
                    push(pop() / op2);
                }
                else
                {
                    printf("error: zero divisor\n");
                }
                break;
            case '\n':
                printf("\t%.8g", pop());
                break;
            default:
                printf("error: unknown command %s, \n", s);
                break;
        }
    }

    return 0;
}