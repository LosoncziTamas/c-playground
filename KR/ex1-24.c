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

int main(void)
{
    int bracketCount = 0;
    int parenthesesCount = 0;
    int braceCount = 0;
    int singleQuoteCount = 0;
    int doubleQuoteCount = 0;
    int blockCommentCount = 0;
    int lastChar = 0;

    for (int c = getchar(); c != EOF; c = getchar())
    {
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

        bool inQuote = doubleQuoteCount % 2;
        if (lastChar == '/' && c == '*' && !inQuote)
        {
            blockCommentCount++;
        }
        else if (lastChar == '*' && c == '/' && !inQuote)
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