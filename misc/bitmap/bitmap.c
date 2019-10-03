#include <stdio.h>
#include "bitmap.h"

#define BUFF_SIZE 1024

#define ArrayCount(x) (sizeof(x) / sizeof(x[0]))

typedef enum LoadError
{
    SUCCESS = 0,
    FILE_OPEN_ERROR = -1,
    BUFF_TOO_SMALL = -2,
    READ_ERROR = -3
} LoadError;

static const struct 
{
    LoadError code;
    char* message;
} ErrorDescriptions[] = 
{
    {SUCCESS, "No error."},
    {FILE_OPEN_ERROR, "File open error."},
    {BUFF_TOO_SMALL, "Buffer to small to read the file."},
    {READ_ERROR, "File reading error."}
};

typedef struct Buffer
{
    unsigned char data[BUFF_SIZE];
    int elementCount;
} Buffer;

LoadError LoadBitmap(const char* path, Buffer* buffer)
{
    // TODO: load header first, use offset to locate pixel data
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

void PrintError(LoadError errorCode)
{
    for (int i = 0; i < ArrayCount(ErrorDescriptions); ++i)
    {
        if (errorCode == ErrorDescriptions[i].code)
        {
            printf("ERROR: %s", ErrorDescriptions[i].message);
        }
    }
}

void PrintHeader(BitmapHeader* header)
{
    printf("height: %d  ", header->bitmapHeight);
    printf("width: %d \n", header->bitmapWidth);
    printf("image size: %d, \n", header->imageSize);
    printf("bits per pixel: %u \n", header->bitsPerPixel);

    for (int i = 0; i < ArrayCount(CompressionMethods); ++i)
    {
        if (header->compressionMethod == CompressionMethods[i].code)
        {
            printf("compression: %d %s \n", CompressionMethods[i].code, CompressionMethods[i].description);
        }
    }
}

typedef union 
{
   unsigned int value;
   struct
   {
       unsigned char b;
       unsigned char g;
       unsigned char r;
       unsigned char a;
   };
} Color32;

int main(int argCount, char **args)
{
    Buffer memory = {0};
    LoadError result = LoadBitmap("bitmap_test.bmp", &memory);
    if (result == SUCCESS)
    {
        // TODO: copy memory
        BitmapHeader* header = (BitmapHeader*)memory.data;
        
        PrintHeader(header);
        
        Color32 *pixelArray = (Color32*)(memory.data + header->offset);

        int h = header->bitmapHeight;
        int w = header->bitmapWidth;        
        for (int rowIndex = 0; rowIndex < h; ++rowIndex)
        {
            for (int columnIndex = 0; columnIndex < w; ++columnIndex)
            {
                Color32 pixelColor = pixelArray[rowIndex * w + columnIndex];
                // Pixels are stored upside-down.
                printf("Pixel[%d][%d] = rgba(%03d, %03d, %03d, %03d) \n", columnIndex, h - 1 - rowIndex, pixelColor.r, pixelColor.g, pixelColor.b, pixelColor.a);
            }
        }
    }
    else
    {
        PrintError(result);
    }
    return 0;
}