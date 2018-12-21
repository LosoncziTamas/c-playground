#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct __attribute__((__packed__)) FileContent
{
    char header[16];
    int versionNumber;
    char content[128];
} FileContent;

int main(void)
{
    FileContent content;
    strcpy(content.header, "Header content.");
    content.versionNumber = 1;
    strcpy(content.content, "This is the content of the file");

    FILE *fp = fopen("testfile2", "wb");

    if (fp)
    {
        size_t result = fwrite(&content, sizeof(content), 1, fp);
        fclose(fp);
    }

    return 0;
}