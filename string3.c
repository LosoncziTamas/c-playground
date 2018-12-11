#include <stdio.h>

size_t stringLength(const char *str)
{
    size_t result = 0;
    for (; *str != '\0'; ++str)
    {
        ++result;
    }
    return result;
}

void reverseString(char *str)
{
    size_t len = stringLength(str);
    for (int i = 0; i < (len / 2); ++i)
    {
        char tmp = str[i];
        str[i] = str[len - (i + 1)];
        str[len - i] = tmp;
    }
    str[len] = '\0';
}

int main(void)
{
    char str[] = "Hello, world";
    reverseString(str);
    printf("%s", str);
    printf("\n");

    return 0;
}