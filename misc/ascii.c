#include <stdio.h>

char toUpperCase(char c) {
    if (c >= 'a' && c <= 'z') {
        c -=  'a' - 'A';
    }
    return c;
}

char toLowerCase(char c) {
    if (c >= 'A' && c <= 'Z') {
        c += 'a' - 'A';
    }
    return c;
}

char invertCase(char c) {
    if (c >= 'A' && c <= 'z') {
        c ^= 1 << 5;
    }
    return c;
}

// ASCII is 7 bit character set
void printAscii() {
    for(unsigned char i = 0; i < 128; ++i) {
        printf("%d: %c ", i, i);
        if (i % 10 == 0) {
            printf("\n");
        }
    }
}

void printNonAscii() {
    for(int i = 128; i < 256; ++i) {
        printf("%d: %c ", i, i);
        if (i % 10 == 0) {
            printf("\n");
        }
    }
}

int main(void) {

    // ASCII value of 'a' is 97
    char lowerCase = 'a';
    // ASCII value of 'a' is 65
    char upperCase = 'A';

    char diff = 'a' - 'A';
    printf("%d %d %d\n", lowerCase, upperCase, diff);

    printAscii();
    printNonAscii();

    printf("%c", toUpperCase('b'));
    printf("%c", toLowerCase('B'));
    printf("%c", invertCase('A'));
    printf("%c", invertCase('a'));

    return 0;
}