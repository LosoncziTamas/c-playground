#include <stdio.h>

#define BUFF_SIZE 1024
#define ArrayCount(x) (sizeof(x) / sizeof(x[0]))

typedef enum LoadError
{
    SUCCESS = 0,
    FILE_OPEN_ERROR = -1,
    BUFF_TOO_SMALL = -2,
    READ_ERROR = -3
} LoadError;

struct ErrorDesc 
{
    int code;
    char* message;
} errorDesc[] = {
    {SUCCESS, "No error."},
    {FILE_OPEN_ERROR, "File open error."},
    {BUFF_TOO_SMALL, "Buffer to small to read the file."},
    {READ_ERROR, "File reading error."}
};

typedef struct Buffer
{
    char data[BUFF_SIZE];
} Buffer;

LoadError LoadBitmap(const char* path, Buffer* buffer)
{
    FILE* file = fopen(path, "r");

    if (!file)
    {
        return FILE_OPEN_ERROR;
    }
    if (fseek(file, 0, SEEK_END) != 0)
    {
        return FILE_OPEN_ERROR;
    }
    long elementCount = ftell(file);
    if (elementCount < 0)
    {
        return FILE_OPEN_ERROR;
    }
    rewind(file);
    if (elementCount > ArrayCount(buffer->data))
    {
        return BUFF_TOO_SMALL;
    }
    int readCount = fread(buffer->data, sizeof(char), elementCount, file);
    if (readCount != elementCount)
    {
        return READ_ERROR;
    }

    fclose(file);

    return SUCCESS;
}

void PrintError(int errorCode)
{
    for (int i = 0; i < ArrayCount(errorDesc); ++i)
    {
        if (errorCode == errorDesc[i].code)
        {
            printf("ERROR: %s", errorDesc[i].message);
        }
    }
}

int ParseArgs(int argCount, char **args)
{
    if (argCount != 2)
    {
        printf("Usage: bitmap <filename> \n");
        return -1;
    }
    return 0;
}

int main(int argCount, char **args)
{
    Buffer memory = {0};
    int result = LoadBitmap("bitmap_test", &memory);
    if (result == SUCCESS)
    {
        
    }
    else
    {
        PrintError(result);
    }
    
    /*
    for (int rowIndex = 0; rowIndex < Image.height; ++rowIndex)
    {
        for (int columnIndex = 0; columnIndex < Image.width; ++columnIndex)
        {
            int pixelStartIndex = Image.width * rowIndex * Image.bytesPerPixel + Image.height * columnIndex * Image.bytesPerPixel; 
            
            unsigned int r = Image.pixelData[pixelStartIndex];
            unsigned int g = Image.pixelData[pixelStartIndex + 1];
            unsigned int b = Image.pixelData[pixelStartIndex + 2];

            printf("r:%u g:%u b:%u \n", r, g, b);
        }
        printf("\n");
    }*/
    return 0;
}