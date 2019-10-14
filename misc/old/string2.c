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

size_t length3(char *str)
{
    size_t size = 0;
    if ((*str) != '\0') {
        ++size;
        size += length3(++str);
    }
    return size;
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

    printf("%zu", length3(str));
    printf("\n");

    // If the string's length is less to the array's length then the array is filled with the char elements + null terminator
    char str3[20] = "This is a string";
    size_t arrayLength = sizeof(str3) / sizeof(str3[0]);
    size_t strLength = length(str3);
    printf("array length: %zu, string length: %zu", arrayLength, strLength);
    printf("\n");

    // If the string's length is more or equal to the array's length then the null terminator will not be appended.
    // So printf will print until it finds a terminator or zero.
    char str4[16] = "This is a string";
    
    printf("%s", str4);
    printf("\n");

    return 0;
}