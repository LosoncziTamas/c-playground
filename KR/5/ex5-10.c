#include "../../utils/loso_utils.c"
#include <ctype.h>

bool IsNumber(const char* string)
{
    uint32 charIndex = 0;
    char c = string[charIndex];

    if (c == '-')
    {
        c = string[++charIndex];
    }

    while (isdigit(c))
    {
        c = string[++charIndex];
    }

    if (c == '.')
    {
        c = string[++charIndex];
    }

    while (isdigit(c))
    {
        c = string[++charIndex];
    }

    return c == '\0';
}

void TestIsNumber()
{
    assert(IsNumber("123"));
    assert(IsNumber("-123"));
    assert(IsNumber("-1.23"));
    assert(!IsNumber("Hello"));
}

float StringToFloat(const char* string)
{
/*
    int32 charIndex = 0;
    char c = string[charIndex];

    int32 sign = c == '-' ? -1 : 1;
    if (sign < 0)
    {
        c = string[++charIndex];
    }

    while ()
*/
    //TODO: implement
    return (float)atof(string);
}

#define MAX 8

static float stack[MAX];
// Index of next free position.
static uint32 stackP;

void Push(float n)
{
    if (stackP < MAX)
    {
        stack[stackP++] = n;
    }
    else
    {
        PrintText("Stack is full.");
    }
}

float Pop()
{
    if (stackP > 0)
    {
        return stack[--stackP];
    }
    else
    {
        PrintText("Stack is empty");
    }
}

int main(int argCount, char **args)
{
    //TODO: trim args?
    //TODO: fix invalid result
    for (uint32 argIndex = 1; argIndex < argCount; ++argIndex)
    {
        char *arg = args[argIndex];
        if (IsNumber(arg))
        {
            float n = StringToFloat(arg);
            Push(n);
        }
        else if (StringsAreEqual(arg, "+"))
        {
            Push(Pop() + Pop());
        }
        else if (StringsAreEqual(arg, "-"))
        {
            float operand = Pop();
            Push(Pop() - operand);
        }
        // TODO: other operands
    }

    printf("\t%8g", Pop());
}