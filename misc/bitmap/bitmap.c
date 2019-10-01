#include <stdio.h>

#define BI_RGB              0
#define BI_RLE8             1
#define BI_RLE4             2
#define BI_BITFIELDS        3
#define BI_JPEG             4
#define BI_PNG              5
#define BI_ALPHABITFIELDS   6
#define BI_CMYK             11
#define BI_CMYKRLE8         12
#define BI_CMYKRLE4         13

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
    LoadError code;
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
    int elementCount;
} Buffer;

typedef struct FileHeader
{
    char headerField[2];
    unsigned int bitmapSize;
    char reserved[4];
    unsigned int offset;
} __attribute__((packed)) FileHeader;

typedef struct DIBHeader
{
    unsigned int headerSize;
    unsigned int bitmapWidth;
    unsigned int bitmapHeight;
    unsigned short colorPlaneCount;
    unsigned short bitsPerPixel;
    unsigned int compressionMethod;
    unsigned int imageSize;
    int horizontalResolution;
    int verticalResolution;
    unsigned int colorPaletteColorCount;
    unsigned int importantColors;
} __attribute__((packed)) DIBHeader;

// TODO: complete bitmap
typedef struct Bitmap
{
    FileHeader fileHeader;
    DIBHeader dibHeader;
} __attribute__((packed)) Bitmap;

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
    buffer->elementCount = elementCount;
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
    LoadError result = LoadBitmap("bitmap_test.bmp", &memory);
    if (result == SUCCESS)
    {
        // TODO: copy memory
        Bitmap* bitmap = (Bitmap*)memory.data;
        printf("height: %d  ", bitmap->dibHeader.bitmapHeight);
        printf("width: %d \n", bitmap->dibHeader.bitmapWidth);
    }
    else
    {
        PrintError(result);
    }
    return 0;
}