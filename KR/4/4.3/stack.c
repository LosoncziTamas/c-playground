#include <stdio.h>

#define MAXVAL 100

static int sp = 0; 
static double val[MAXVAL];

void printStack() 
{
    int len = sp;
    printf("stack content: ");
    while(len--) {
        printf(" %.8g", val[len]);
    }
    printf(" \n");
}

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
    printStack();
}

double pop()
{
    if (sp > 0)
    {
        return val[--sp];
    }
    else 
    {
        printf("pop error: stack empty \n");
        return 0.0;
    }
}

double top()
{
    if (sp > 0)
    {
        return val[sp - 1];
    }
    else
    {
        printf("top error: stack empty\n");
        return 0.0;
    } 
}


void clear()
{
    while (sp--)
    {
        pop();
    }
}
