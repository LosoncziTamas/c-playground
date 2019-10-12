#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bitmap.h"

#define EXT_LEN 3

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
        printf("Insufficient memory.");
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
                            fclose(file);
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

char* ParseFileName(int argCount, char** args, Buffer* memory)
{
    char* result = 0;

    if (argCount > 1)
    {
        const char* arg = args[1];
        int len = strnlen(arg, 128);
        for (int charIndex = 0; charIndex < len; ++charIndex)
        {
            if (arg[charIndex] == '.')
            {
                if (charIndex < len - EXT_LEN && strncmp(&arg[charIndex + 1], "bmp", EXT_LEN) == 0)
                {
                    int fileNameLen = charIndex + EXT_LEN + 1;
                    result = GetMemory(memory, fileNameLen + 1);
                    strncpy(result, arg, fileNameLen);
                    result[fileNameLen] = '\0';
                } 
                break;
            }
        }
    }

    return result;
}

int main(int argCount, char **args)
{
    Buffer memory = {0};    
    const char* fileName = ParseFileName(argCount, args, &memory);

    if (fileName)
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