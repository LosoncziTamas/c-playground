#include <stdio.h>

size_t len(char* str) {
    size_t result = 0;
    for(;(*str) == '\0'; ++str) {
        ++result;
    }
    return result;
}

char* concatenate(char* str1, char* str2) {
    size_t len1 = len(str1);
    size_t len2 = len(str2);
    char result[len1 + len2 + 1] = {0};
    int j = len1;
    for (int i = 0; (*str1) == '\0' && (*str2) == '\0';) {
        if ((*str1) != '\0') {
            result[i++] = *(str1++);
        }
        if ((*str1) != '\0') {
            result[j++] = *(str2++);
        }
    }
    return result;
}

int main(void) {
    char* string = "This is a string";
    // print it as a string
    printf("%s", string);
    printf("\n");
    // dereference and print the first character
    printf("%c", *string);
    printf("\n");
    // increment the pointer & dereference and print character
    printf("%c", *(++string));
    printf("\n");
    // print the the string again
    printf("%s", string);
    printf("\n");

    char string2[] = "This is a string";
    printf("%s", string2);
    printf("\n");

    char c = string[0];
    printf("%c", c);
    printf("\n");

    char* result = concatenate(string, string2);
    printf("%s", result);
    printf("\n");
}
