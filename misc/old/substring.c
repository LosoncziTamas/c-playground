#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

char* substr(const char* str, unsigned int start, unsigned int end) {
    assert(start < end);
    size_t len = end - start;
    char* result = malloc((len + 1) * sizeof(char));
    for(unsigned int resultIndex = 0, sourceIndex = start; resultIndex < len; ++resultIndex, ++sourceIndex) {
        result[resultIndex] = str[sourceIndex];
    }
    result[len] = '\0';
    return result;
}


int main(void) {

    const char* str = "This is a string";

    char* result = substr(str, 0, 4);
    printf("%s \n", result);

    char* result2 = substr(str, 5, 7);
    printf("%s \n", result2);

    char* result3 = substr(str, 8, 9);
    printf("%s \n", result3);

    char* result4 = substr(str, 10, 16);
    printf("%s \n", result4);

    free(result);
    free(result2);
    free(result3);
    free(result4);

    return 0;
}