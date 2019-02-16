#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

/*  How would you test the word count program? 
    What kinds of input are most likely to
    uncover bugs if there are any? */

int main(void)
{
    int lineCount, wordCount, charCount;

    lineCount = wordCount = charCount = 0;
    bool outsideWord = true;
    for (int c = getchar(); c != EOF; c = getchar())
    {
        ++charCount;
        if (c == '\n')
        {
            ++lineCount;
        }
        if (c == ' ' || c == '\n' || c == '\t')
        {
            outsideWord = true;
        }
        else if (outsideWord)
        {
            outsideWord = false;
            ++wordCount;
        }
    }
    printf("%d %d %d\n", lineCount, wordCount, charCount);
}