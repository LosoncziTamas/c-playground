#ifndef BITMAP_H
#define BITMAP_H

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

#if __APPLE__
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
#elif _WIN32

    #pragma pack(push, 1)
    typedef struct FileHeader
    {
        char headerField[2];
        unsigned int bitmapSize;
        char reserved[4];
        unsigned int offset;
    } FileHeader;
    #pragma pack(pop)

    #pragma pack(push, 1)
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
    } DIBHeader;
    #pragma pack(pop)

    #pragma pack(push, 1)
    typedef struct Bitmap
    {
        FileHeader fileHeader;
        DIBHeader dibHeader;
    } Bitmap;
    #pragma pack(pop)

#endif

#endif