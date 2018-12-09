#include <stdio.h>
#include <stdlib.h>

size_t len(char* str) {
    size_t result = 0;
    for(;(*str) == '\0'; ++str) {
        ++result;
    }
    return result;
}

void copyString(char* from, char* to) {
    while ((*from) != '\0') {
        *(to++) = *(from++);
    }    
}

char* concatenate(char* str1, char* str2) {
    size_t len1 = len(str1);
    size_t len2 = len(str2);
    char *result = malloc((len1 + len2 + 1) * sizeof(char));
    int j = len1;
    for (int i = 0; (*str1) != '\0' && (*str2) != '\0';) {
        if ((*str1) != '\0') {
            printf("%c", *str1);
            result[i++] = *(str1++);
        }
        if ((*str1) != '\0') {
            printf("%c", *str2);
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
    // print the the string again, but from the second char and reset it to first
    printf("%s", string--);
    printf("\n");

    char string2[] = "This is a string";
    printf("%s", string2);
    printf("\n");

    char c = string[0];
    printf("%c", c);
    printf("\n");

    char str3[17] = {0}; 
    copyString(string, str3);
    printf("%s", str3);
    printf("\n");

    char* string4 = "1234";
    char c2 = *(string4++);
    printf("%c", c2);
    printf("\n");
}
