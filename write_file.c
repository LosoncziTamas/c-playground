#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct __attribute__((__packed__)) FileContent
{
    char header[16];
    int versionNumber;
    char content[128];
} FileContent;

void writeFile(const char* fileName, FileContent* content) 
{    
    FILE *fp = fopen(fileName, "wb");
    if (fp)
    {
        size_t result = fwrite(content, sizeof(FileContent), 1, fp);
        printf("%zu number of data written to %s\n", result, fileName);
        fclose(fp);
    }
}

void readFile(const char* fileName) 
{
    FILE* fp = fopen(fileName, "rb");
    if(fp)
    {
        fseek(fp, 0, SEEK_END);
        long size = ftell(fp);
        rewind(fp);
        
        void* buff = malloc(sizeof(char) * size);
        fread(buff, sizeof(char) * size, 1, fp);
        fclose(fp);

        FileContent* content = (FileContent*) buff;
        printf("%s \n", content->header);
        printf("%d \n", content->versionNumber);
        printf("%s \n", content->content);
        free(content);
    }
}

int main(void)
{
    FileContent content = {0};
    strcpy(content.header, "Header content.");
    content.versionNumber = 1;
    strcpy(content.content, "This is the content of the file");

    writeFile("testfile2", &content);
    readFile("testfile2");

    return 0;
}