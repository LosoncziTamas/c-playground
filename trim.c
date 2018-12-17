#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

size_t stringLength(const char *str)
{
    size_t result = 0;
    while (*(str++) != 0)
    {
        ++result;
    }
    return result;
}

char *duplicateString(const char *src, size_t len)
{
    char *result = malloc((len + 1) * sizeof(char));
    char *start = result;
    for(int i = 0; i < len; ++i) {
        *(start++) = *(src++);
    }
    result[len] = '\0';
    return result;
}

char* trimString(const char* str) 
{
    size_t len = stringLength(str);
    size_t startSpaceCount = 0;
    const char *start = str;

    while (isspace(*(start++)))
    {
        ++startSpaceCount;
    }
    size_t endSpaceCount = 0;
    const char *end = &str[len - 1];
    while (isspace(*(end--)))
    {
        ++endSpaceCount;
    }

    char *result = duplicateString(str + startSpaceCount, len - (startSpaceCount + endSpaceCount));
    return result;
}

int main(void)
{
    const char *str = " This is a string. ";
    printf("%s \n", str);
    char *trimmedStr = trimString(str);
    printf("%s \n", trimmedStr);
    
    free(trimmedStr);
    return 0;
}