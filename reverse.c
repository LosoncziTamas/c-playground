#include <stdio.h>
#include <stdlib.h>

size_t stringLength(const char *str)
{
    size_t result = 0;
    for (; *str != '\0'; ++str)
    {
        ++result;
    }
    return result;
}

void copyString(const char* src, size_t srcLen, char* dest) 
{
    while(srcLen--) 
    {
        *(dest++) = *(src++);
    }
}

char* duplicateString(const char* str) 
{
    size_t len = stringLength(str);
    char* result = malloc((len + 1) * sizeof(char));
    copyString(str, len, result);
    return result;
}

void reverseStringInPlace(char *str)
{
    size_t len = stringLength(str);
    for (int i = 0; i < (len / 2); ++i)
    {
        char tmp = str[i];
        str[i] = str[len - (i + 1)];
        str[len - (i + 1)] = tmp;
    }
    str[len] = '\0';
}

char* reverseString(const char* str) 
{
    char* result = duplicateString(str);
    reverseStringInPlace(result);
    return result;
}

int main(void)
{
    char str[] = "Hello, world";
    reverseStringInPlace(str);
    printf("%s", str);
    printf("\n");

    char* newStr = reverseString(str);
    printf("%s", newStr);
    printf("\n");
    free(newStr);

    return 0;
}