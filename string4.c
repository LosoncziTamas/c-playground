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
    // fix underflow here
    while (len--)
    {
        *(++result) = *(++src);
    }
    result[len] = '\0';
    // return front, not the end
    return result;
}

int main(void)
{
    const char *str = "  This is a string. ";
    size_t len = stringLength(str);

    char *copy = duplicateString(str, len);

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

    return 0;
}