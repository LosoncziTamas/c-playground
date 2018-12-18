#include <stdio.h>

int main(void) {

    FILE* fp = fopen("testfile.txt", "r");
    if (fp) {
        fprintf(stdout, "File opened");
    } else {
        fprintf(stderr, "Couldn't open file");
    }

    fclose(fp);

    return 0;
}