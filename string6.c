#include <stdio.h>

char toUpperCase(char c) {
    if (c >= 'a' && c <= 'z') {
        c -=  'a' - 'A';
    }
    return c;
}

int main(void) {

    // ASCII value of 'a' is 97
    char lowerCase = 'a';
    // ASCII value of 'a' is 65
    char upperCase = 'A';

    char diff = 'a' - 'A';

    printf("%d %d %d\n", lowerCase, upperCase, diff);
    printf("%c", toUpperCase('b'));

    return 0;
}