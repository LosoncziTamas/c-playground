#include <stdio.h>
#include <stdbool.h>

/*  Write a program to check a C program
    for rudimentary syntax errors like 
    unbalanced parentheses, brackets and 
    braces. Don't forget about quotes, 
    both single and double, escape 
    sequences, and comments. */

typedef struct Syntax
{
    unsigned int flags;
    int braceBalance;
    int bracketBalance;
    int parenthesesBalance;
    int singleQuoteCount;
    int doubleQuoteCount;
} Syntax;

enum EscapeFlags
{
    NONE = 0,
    SINGLE_QUOTE = (1 << 0),
    DOUBLE_QUOTE = (1 << 1),
    ESCAPE_SEQ = (1 << 2),
    LINE_COMMENT = (1 << 3),
    BLOCK_COMMENT = (1 << 4)
};

void setFlag(Syntax *syntax, unsigned int flag)
{
    syntax->flags |= flag;
}

bool isSet(Syntax *syntax, unsigned int flag)
{
    return syntax->flags & flag;
}

void clearFlag(Syntax *syntax, unsigned int flag)
{
    syntax->flags &= ~flag; 
}

int main(void)
{
    Syntax syntax = {0};
    for (int c = getchar(), lastChar = 0; c != EOF; c = getchar())
    {
        if (isSet(&syntax, ESCAPE_SEQ))
        {
            lastChar = c;
            clearFlag(&syntax, ESCAPE_SEQ);
            continue;
        }
        if (c == '\\')
        {
            setFlag(&syntax, ESCAPE_SEQ);   
        }
        else
        {
            clearFlag(&syntax, ESCAPE_SEQ);
        }

        if (!isSet(&syntax, BLOCK_COMMENT | DOUBLE_QUOTE | SINGLE_QUOTE))
        {
            if (lastChar == '/' && c == '/')
            {
                setFlag(&syntax, LINE_COMMENT);
            } 
            else if (c == '\n')
            {
                clearFlag(&syntax, LINE_COMMENT);
            }
        }

        if (!isSet(&syntax, LINE_COMMENT | DOUBLE_QUOTE | SINGLE_QUOTE))
        {
            if (lastChar == '/' && c == '*')
            {
                setFlag(&syntax, BLOCK_COMMENT);
            }
            else if (lastChar == '*' && c == '/')
            {
                clearFlag(&syntax, BLOCK_COMMENT);
            }
        }

        if (!isSet(&syntax, LINE_COMMENT | BLOCK_COMMENT | SINGLE_QUOTE))
        {
            if (c == '\"')
            {
                syntax.doubleQuoteCount++;
                if (isSet(&syntax, DOUBLE_QUOTE))
                {
                    clearFlag(&syntax, DOUBLE_QUOTE);
                }
                else
                {
                    setFlag(&syntax, DOUBLE_QUOTE);
                }
            }
        }

        if (!isSet(&syntax, LINE_COMMENT | BLOCK_COMMENT | DOUBLE_QUOTE))
        {
            if (c == '\'')
            {
                syntax.singleQuoteCount++;
                if (isSet(&syntax, SINGLE_QUOTE))
                {
                    clearFlag(&syntax, SINGLE_QUOTE);
                }
                else
                {
                    setFlag(&syntax, SINGLE_QUOTE);
                }
            }
        }

        if (!isSet(&syntax, LINE_COMMENT | BLOCK_COMMENT | DOUBLE_QUOTE | SINGLE_QUOTE))
        {
            switch (c)
            {
            case '[':
                syntax.bracketBalance++;
                break;
            case ']':
                syntax.bracketBalance--;
                break;
            case '(':
                syntax.parenthesesBalance++;
                break;
            case ')':
                syntax.parenthesesBalance--;
                break;
            case '{':
                syntax.braceBalance++;
                break;
            case '}':
                syntax.braceBalance--;
                break;
            default:
                break;
            }
        }

        lastChar = c;
    }

    if (syntax.bracketBalance)
    {
        puts("Unbalanced brackets.");
    }
    if (syntax.parenthesesBalance)
    {
        puts("Unbalanced parentheses.");
    }
    if (syntax.braceBalance)
    {
        puts("Unbalanced braces.");
    }
    if (syntax.singleQuoteCount % 2)
    {
        puts("Unbalanced single quote.");
    }
    if (syntax.doubleQuoteCount % 2)
    {
        puts("Unbalanced double quote.");
    }
    if (isSet(&syntax, BLOCK_COMMENT))
    {
        puts("Unbalanced comment block.");
    }

    return 0;
}