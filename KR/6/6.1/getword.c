#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "common.h"

#define MAXWORD 100

struct Key {
    char* word;
    int count;
} Keytab[] = {
    "auto", 0,
    "break", 0,
    "case", 0,
    "char", 0,
    "const", 0,
    "continue", 0,
    "default", 0,
    //...
    "unsigned", 0,
    "void", 0,
    "volatile", 0,
    "while", 0
};

int GetWord(char* word, int lim)
{
    int c;
    while (isspace(c = GetChar()));

    char* w = word;
    if (c != EOF)
    {
        *w++ = c;
    }
    // If first read char is not alphabetical then return.
    if (!isalpha(c))
    {
        *w = '\0';
        return c;
    }

    // If read char is not alpanumeric then push it back.
    for (; --lim > 0; w++)
    {
        if (!isalnum(*w = GetChar()))
        {
            UngetChar(*w);
            break;
        }
    }
    *w = '\0';

    return word[0];
}

int BinSearch(char* word, struct Key tab[], int tabCount)
{
    int low = 0;
    int high = tabCount - 1;

    while (low <= high)
    {
        int mid = (low + high) / 2;
        int result = strcmp(word, tab[mid].word);
        // Searched word is between low and mid.
        if (result < 0) 
        {
            high = mid - 1;
        }
        // Searched word is between high and mid.
        else if (result > 0)
        {
            low = mid + 1;
        }
        else
        {
            return mid;
        }
    }

    return -1;
}

int main()
{
    Stream memoryStream = {0};
    strcpy(memoryStream.data, "continue this text\n break hello continue");
    memoryStream.type = Memory;
    SetStream(&memoryStream);

    char word[MAXWORD];

    while (GetWord(word, MAXWORD) != EOF)
    {
        if (isalpha(word[0]))
        {
            int keywordIndex = BinSearch(word, Keytab, ArrayCount(Keytab));
            if (keywordIndex > -1)
            {
                Keytab[keywordIndex].count++;
            }
        }
    }

    for (int keywordIndex = 0; keywordIndex < ArrayCount(Keytab); keywordIndex++)
    {
        if (Keytab[keywordIndex].count > 0)
        {
            printf("%4d %s\n", Keytab[keywordIndex].count, Keytab[keywordIndex].word);
        }
    }

    return 0;
}

