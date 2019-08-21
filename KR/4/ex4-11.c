#include <stdio.h>
#include <math.h>
#include <ctype.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char str[]);
void push(double n);
double pop();

#define MAXVAL 100

int sp = 0; 
double val[MAXVAL];

void push(double f)
{
    if (sp < MAXVAL)
    {
        val[sp++] = f;
    } 
    else 
    {
        printf("error: stack full, can't push %g\n", f);
    }
}

double pop()
{
    if (sp > 0)
    {
        return val[--sp];
    }
    else 
    {
        printf("error: stack empty \n");
        return 0.0;
    }
}

#define BUFSIZE 100

int getop(char s[])
{
    static int chBuff[BUFSIZE];
    static int bufp = 0;
    int i, c;

    c = bufp > 0 ? chBuff[--bufp] : getchar();
    s[0] = c;
    while(c == ' ' || c == '\t')
    {
        c = bufp > 0 ? chBuff[--bufp] : getchar();
        s[0] = c;
    }

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
        c = bufp > 0 ? chBuff[--bufp] : getchar();
        s[++i] = c;
        while (isdigit(c))
        {
            c = bufp > 0 ? chBuff[--bufp] : getchar();
            s[++i] = c;
        }
    }
    // collect fraction
    if (c == '.')
    {   
        c = bufp > 0 ? chBuff[--bufp] : getchar();
        s[++i] = c;
        while (isdigit(c))
        {
            c = bufp > 0 ? chBuff[--bufp] : getchar();
            s[++i] = c;
        }
    }
    s[i] = '\0';
    if (c != EOF)
    {
        chBuff[bufp++] = c;
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
            printf("\t%.8g\n", pop());
            break;
        default:
            printf("error: unknown command %s, \n", s);
            break;
        }
    }

    return 0;
}