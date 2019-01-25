#include <stdio.h>
#include <stdbool.h>
/*
    Write a program to remove all
    comments from a C program. 
    Don't forget to handle quoted
    strings and character constants properly. 
    C comments do not nest.
*/

/*
    Step 1: Read till EOF
    Step 2: Identify comment start
        a: Single line comment
        b: Comment block
    Step 3: Skip until line or block end.
        
*/

int main(void)
{

    bool inQuote = false;
    for (int c = getchar(); c != EOF; c = getchar())
    {
        if (c == '"')
        {
            inQuote = !inQuote;
        }
    }
    return 0;
}