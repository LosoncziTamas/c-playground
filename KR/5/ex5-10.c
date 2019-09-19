#include "../../utils/loso_utils.c"
#include <ctype.h>

bool IsNumber(const char* string)
{
    uint32 charIndex = 0;
    char c = string[charIndex];
    uint32 len = StringLength(string);

    if (c == '-' && len > 1)
    {
        c = string[++charIndex];
    }

    while (isdigit(c))
    {
        c = string[++charIndex];
    }

    if (c == '.' && len > 2)
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
    assert(!IsNumber("-"));
    assert(!IsNumber("."));
    assert(!IsNumber(".."));
    assert(!IsNumber(".-"));
    assert(!IsNumber("-."));
}

float StringToFloat(const char* string)
{
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
        else if (StringsAreEqual(arg, "*"))
        {
            Push(Pop() * Pop());
        }
        else if (StringsAreEqual(arg, "/"))
        {
            float operand = Pop();
            if (operand != 0)
            {
                Push(Pop() / operand);
            }
            else
            {
                PrintText("ERROR: division by zero");
                break;
            }
        }
    }

    printf("\t%f", Pop());
}