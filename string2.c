#include <stdio.h>

void printFirstChar(char *str)
{
    char *c = &str[0];
    printf("%c", *c);

    char *c2 = str;
    printf("%c", *c2);

    char c3 = (*str);
    printf("%c", c3);

    char c4 = str[0];
    printf("%c", c4);
    printf("\n");
}

// Everything is passed by value, this will not change the original parameter
void movePointer(char *str)
{
    ++str;
    printf("%s", str);
    printf("\n");
}

size_t length(char *str)
{
    size_t len = 0;
    while (*(str++) != '\0')
    {
        ++len;
    }
    return len;
}

size_t length2(char *str)
{
    size_t len = 0;
    for (; *str != '\0'; ++str)
    {
        ++len;
    }
    return len;
}

int main(void)
{
    char *str = "This is a string";
    printFirstChar(str);

    char str2[] = "This is a string";
    printFirstChar(str2);

    movePointer(str);
    printf("%s", str);
    printf("\n");

    printf("%zu", length(str));
    printf("\n");

    printf("%zu", length2(str2));
    printf("\n");

    return 0;
}