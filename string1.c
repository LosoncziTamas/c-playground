#include <stdio.h>

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
}
