#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bitmap.h"

unsigned char* GetMemory(Buffer* buffer, size_t size)
{
    unsigned char* result = 0;

    if (size < ArrayCount(buffer->data) - buffer->buffP)
    {
        result = buffer->data + buffer->buffP;
        buffer->buffP += size;
    }
    else 
    {
        printf("Unsufficient memory.");
        exit(1);
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
            printf("Compression: %d %s \n", CompressionMethods[i].code, CompressionMethods[i].description);
        }
    }
}

ProgramError LoadBitmap(const char* path, Buffer* buffer, PixelArray32* pixelArray)
{
    FILE* file = fopen(path, "r");

    if (file)
    {
        if (fseek(file, 0, SEEK_END) == 0)
        {
            int elementCount = ftell(file);
            if (ftell(file) > sizeof(BitmapHeader))
            {
                BitmapHeader* header = (BitmapHeader*) GetMemory(buffer, sizeof(BitmapHeader));
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

                            if (header->imageSize == fread(pixelArray->pixels, 1, header->imageSize, file))
                            {
                                fclose(file);
                                return SUCCESS;
                            }
                        }
                        else
                        {
                            return UNSUPPORTED_FORMAT;
                        }
                    }
                }
            }
        }
        fclose(file);
        return FREAD_ERROR;
    }

    return FOPEN_ERROR;
}

void PrintError(ProgramError errorCode)
{
    for (int i = 0; i < ArrayCount(ErrorDescriptions); ++i)
    {
        if (errorCode == ErrorDescriptions[i].code)
        {
            printf("ERROR: %s", ErrorDescriptions[i].message);
        }
    }
}

// TODO: fix parsing
ProgramError ParseArgs(int argCount, char** args, Buffer* memory, char* fileName)
{
    ProgramError result = INVALID_ARGS;

    if (argCount > 1)
    {
        const char* arg = args[1];
        int len = strnlen(arg, 128);
        for (int charIndex = 0; charIndex < len; ++charIndex)
        {
            if (arg[charIndex] == '.')
            {
                if (charIndex < len - 3 && strncmp(&arg[charIndex + 1], "bmp", 3) == 0)
                {
                    fileName = GetMemory(memory, charIndex + 3);
                    strncat(fileName, arg, charIndex + 3);
                    result = SUCCESS;
                } 
                break;
            }
        }
    }

    return result;
}

int main(int argCount, char **args)
{
    // Create memory buffer on the stack
    Buffer memory = {0};

    char* fileName;
    if (ParseArgs(argCount, args, &memory, fileName) == SUCCESS)
    {
        PixelArray32 pixelArray = {0};
        ProgramError result = LoadBitmap(fileName, &memory, &pixelArray);
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
                    printf("Pixel[%d][%d] = rgba(%03d, %03d, %03d, %03d) \n",h - 1 - rowIndex, columnIndex, pixelColor.r, pixelColor.g, pixelColor.b, pixelColor.a);
                }
            }
        }
        else
        {
            PrintError(result);
        }
    }
    else
    {
        printf("Usage: bitmap <filename>");
    }

    return 0;
}