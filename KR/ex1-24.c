#include <stdio.h>
#include <stdbool.h>

/*  Write a program to check a C program
    for rudimentary syntax errors like 
    unbalanced parentheses, brackets and 
    braces. Don't forget about quotes, 
    both single and double, escape 
    sequences, and comments. */

/*
    Step 1: Read til EOF
    Step 2: Check pairity of [], (), {}, '', "", \
*/

typedef struct Syntax
{
    unsigned int flags;
} Syntax;

typedef enum Flags
{
    NONE = 0,
    BRACKET = (1 << 0),
    PARENTHESES = (1 << 1),
    BRACE = (1 << 2),
    SINGLE_QUOTE = (1 << 3),
    DOUBLE_QUOTE = (1 << 4),
    ESCAPE_SEQ = (1 << 5),
    LINE_COMMENT = (1 << 6),
    BLOCK_COMMENT = (1 << 7)
} Flags;

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
        // check for escaping chars
        if (lastChar == '/' && c == '/')
        {
            setFlag(&syntax, LINE_COMMENT);
        } 
        else if (c == '\n')
        {
            clearFlag(&syntax, LINE_COMMENT);
        }


        lastChar = c;
    }
    return 0;
}


int oldmain(void)
{
    int bracketCount = 0;
    int parenthesesCount = 0;
    int braceCount = 0;
    int singleQuoteCount = 0;
    int doubleQuoteCount = 0;
    int blockCommentCount = 0;
    int lastChar = 0;
    bool inLineComment = false;

    for (int c = getchar(); c != EOF; c = getchar())
    {
        if (lastChar == '/' && c == '/')
        {
            inLineComment = true;
        } 
        else if (c == '\n')
        {
            inLineComment = false;
        }

        bool inQuote = doubleQuoteCount % 2;

        if (inQuote || inLineComment)
        {
            lastChar = c;
            continue;
        }

        switch (c)
        {
            case '[':
                bracketCount++;
                break;
            case ']':
                bracketCount--;
                break;
            case '(':
                parenthesesCount++;
                break;
            case ')':
                parenthesesCount--;
                break;
            case '{':
                braceCount++;
                break;
            case '}':
                braceCount--;
                break;
            case '\'':
                singleQuoteCount++;
                break;
            case '\"':
                doubleQuoteCount++;
                break;
            default:
                break;
        }

        if (lastChar == '/' && c == '*' && !inQuote && !inLineComment)
        {
            blockCommentCount++;
        }
        else if (lastChar == '*' && c == '/' && !inQuote && !inLineComment)
        {
            blockCommentCount--;
        }

        //TODO: check escape sequences

        lastChar = c;
    }

    if (bracketCount)
    {
        puts("Unbalanced brackets.");
    }
    if (parenthesesCount)
    {
        puts("Unbalanced parentheses.");
    }
    if (braceCount)
    {
        puts("Unbalanced braces.");
    }
    if (singleQuoteCount % 2)
    {
        puts("Unbalanced single quote.");
    }
    if (doubleQuoteCount % 2)
    {
        puts("Unbalanced double quote.");
    }
    if (blockCommentCount)
    {
        puts("Unbalanced comment block.");
    }

    return 0;
}