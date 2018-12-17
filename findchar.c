#include <stdio.h>

int findChar(const char* str, char c) {
    for(int i = 0; *str != '\0'; ++str, ++i) {
        if (*str == c) {
            return i;
        }
    }
    return -1;
}

int main(void) {

    const char* str = "This is a string again.";

    char c = 'a';
    int result = findChar(str, c);

    if (result != -1) {
        printf("char %c found at index %d \n", c, result);
        printf("%c \n", str[result]);
    } else {
        printf("char %c not found in %s \n", c, str);
    }

    return 0;
}