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
    int buffP;
} Buffer;

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

typedef struct PixelArray32
{
    Color32* pixels;
    unsigned int w;
    unsigned int h;
} PixelArray32;

// TODO: do i really need this?
unsigned char* GetMemory(Buffer* buffer, size_t size)
{
    unsigned char* result = 0;

    if (size < ArrayCount(buffer->data) - buffer->buffP)
    {
        result = buffer->data + buffer->buffP;
        buffer->buffP += size;
    }

    return result;
}

void PrintHeader(BitmapHeader* header)
{
    printf("Height: %d  ", header->bitmapHeight);
    printf("Width: %d \n", header->bitmapWidth);
    printf("Image size: %d, \n", header->imageSize);
    printf("Bits per pixel: %u \n", header->bitsPerPixel);

    for (int i = 0; i < ArrayCount(CompressionMethods); ++i)
    {
        if (header->compressionMethod == CompressionMethods[i].code)
        {
            printf("compression: %d %s \n", CompressionMethods[i].code, CompressionMethods[i].description);
        }
    }
}

LoadError LoadBitmap(const char* path, Buffer* buffer, PixelArray32* pixelArray)
{
    LoadError result = SUCCESS;
    FILE* file = fopen(path, "r");

    if (file)
    {
        if (fseek(file, 0, SEEK_END) == 0)
        {
            int elementCount = ftell(file);
            if (elementCount > sizeof(BitmapHeader))
            {
                BitmapHeader* header = (BitmapHeader*) GetMemory(buffer, sizeof(BitmapHeader));
                if (header)
                {
                    rewind(file);
                    if (fread(header, sizeof(BitmapHeader), 1, file) == 1)
                    {
                        PrintHeader(header);
                        if (fseek(file, header->offset, SEEK_SET) == 0)
                        {
                            if (header->bitsPerPixel == 32)
                            {
                                pixelArray->h = header->bitmapHeight;
                                pixelArray->w = header->bitmapWidth;
                                pixelArray->pixels = (Color32*) GetMemory(buffer, header->imageSize);
                                // TODO: assert image size?
                                fread(pixelArray->pixels, 1, header->imageSize, file);
                            }
                            else
                            {
                                // TOOD: error handling
                            }
                        }
                        else
                        {
                            result = READ_ERROR;
                        }

                    }
                    else
                    {
                        result = READ_ERROR;
                    }
                }
                else
                {
                    // TODO: Do i need this here?
                    result = BUFF_TOO_SMALL;
                }
            }
        }
        else
        {
            result = READ_ERROR;
        }
        fclose(file);
    }
    else
    {
        result = FILE_OPEN_ERROR;
    }

    return result;
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

//TODO: parsing args
int main(int argCount, char **args)
{
    Buffer memory = {0};
    PixelArray32 pixelArray = {0};

    LoadError result = LoadBitmap("bitmap_test.bmp", &memory, &pixelArray);
    if (result == SUCCESS)
    {        
        int h = pixelArray.h;
        int w = pixelArray.w;        
        for (int rowIndex = 0; rowIndex < h; ++rowIndex)
        {
            for (int columnIndex = 0; columnIndex < w; ++columnIndex)
            {
                Color32 pixelColor = pixelArray.pixels[rowIndex * w + columnIndex];
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