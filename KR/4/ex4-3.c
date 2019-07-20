#include <stdio.h>

#define MAXOP 100
#define NUMBER '0'

int getops(char str[]);

int main()
{
    int type;
    char s[MAXOP];

    while((type = getops(s)) != EOF) 
    {
        switch (type)
        {
        case NUMBER:
            
            break;
        case '+':
            
            break;
        case '-':
            
            break;
        case '*':
            
            break;
        case '/':
            
            break;
        case '\n':
            
            break;
        default:
            break;
        }
    }

    return 0;
}