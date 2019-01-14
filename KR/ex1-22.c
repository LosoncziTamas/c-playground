#include <stdio.h>

/*  Write a program to "fold" long input lines
    into two or more shorter lines after the 
    last non-blank character that occurs before
    the n-th column of input. Make sure your 
    program does something intelligent with 
    very long lines, and if there are no blanks
     or tabs before the specified column. */

    // read til EOF
    // count & store chars in array (n-sized)
    // keep track of last blank & check limit
    // if limit is over then print until the last blank (excluding it), print new line & move the remainder, update variables
    // if limit is not over and new line, then print the array and clear variables
    // if there are no blanks and limits is over, then split

#define MAX_LENGTH 32

int main(void)
{
    char line[MAX_LENGTH] = {0};
    for(int c = getchar(), charIndex = 0, lastBlankIndex = 0; c != EOF; c = getchar())
    {
        if (charIndex < MAX_LENGTH)
        {
            if (c == ' ' || c == '\t')
            {
                // tab takes more space
                lastBlankIndex = charIndex;
            }
            else
            {

            }
        }
        else
        {

        }
        charIndex++;
    }
    return 0;
}