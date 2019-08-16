#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#include "stack.c"

#define BUFSIZE 100
#define NUMBER '0'
#define MAXOP 100
#define MAXVAR 26

/*  
    4-3: add modulus operator
    4-4: print, duplicate, swap top elements
    4-5: sin, exp, pow
    4-6: handling variables
    4-7: ungets
    4-10: use getline
*/

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
    if (bufp == 0 || buf[bufp] == '\0')
    {
        bufp = 0;
        //TODO: clear buffer
        getline(buf, BUFSIZE);
    }

    int c = buf[bufp++];
    while(c == ' ' || c == '\t') 
    {
        c = buf[bufp++];
    }
    if (!isdigit(c) && c != '.') {
        return c;
    }

    int i = 0;
    if (isdigit(c)) {
        s[i++] = c;
        c = buf[bufp++];
        while(isdigit(c))
        {
            s[i++] = c;
            c = buf[bufp++];
        }
    }

    if (c == '.') {
        s[i++] = c;
        c = buf[bufp++];
        while(isdigit(c))
        {
            s[i++] = c;
            c = buf[bufp++];
        }
    }
    s[i] = '\0';

    return NUMBER;
}

int main()
{
    int type, var = 0;
    double op2, v;
    char s[MAXOP];

    double variables[MAXVAR];
    for(int i = 0; i < MAXVAR; ++i)
    {
        variables[i] = 0.0;
    }

    while((type = getop(s)) != EOF) 
    {
        switch (type)
        {
            case NUMBER:
            {
                push(atof(s));
            } break;
            case '+':
            {
                push(pop() + pop());
            } break;
            case '-':
            {
                op2 = pop();
                push(pop() - op2);
            } break;
            case '*':
            {
                push(pop() * pop());
            } break;
            case '^':
            {
                op2 = pop();
                push(pow(pop(), op2));
            } break;
            case 'e':
            {
                push(exp(pop()));
            } break;
            case 's':
            {
                push(sin(pop()));
            } break;
            case '/':
            {
                op2 = pop();
                if (op2 != 0.0) 
                {
                    push(pop() / op2);
                }
                else
                {
                    printf("error: zero divisor\n");
                }
            } break;
            case '%':
            {
                op2 = pop();
                if (op2 == 0.0) 
                {
                    printf("error: zero divisor\n");
                }
                else 
                {
                    push(fmod(pop(), op2));
                }
            } break;
            case '\n':
            {
                v = pop();
                printf("\t%.8g\n", v);
            } break;
            case '?':
            {
                printf("\t%.8g\n", top());
            } break;
            case 'd':
            {
                push(top());
            } break;
            case 'w':
            {
                op2 = pop();
                double op1 = pop();
                push(op2);
                push(op1);
            } break;
            case 'c':
            {
                clear();
            } break;
            case '=':
            {
                pop();
                if (var >= 'A' && var <= 'Z')
                {
                    int varIndex = var - 'A';
                    variables[varIndex] = pop();
                }
                else
                {
                    printf("error: invalid variable %s, \n", var);
                }
            } break;
            case 'v':
            {
                push(v);
            }
            default:
            {
                if (type >= 'A' && type <= 'Z')
                {
                    int varIndex = type - 'A';
                    push(variables[varIndex]);
                }
                else
                {
                    printf("error: unknown command %s, \n", s);
                }
            } break;
            var = type;
        }
    }

    return 0;
}