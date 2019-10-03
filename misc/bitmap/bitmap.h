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

static const struct 
{
    unsigned int code;
    const char* description;
} CompressionMethods[] = 
{
    {BI_RGB, "None"},
    {BI_RLE8, "RLE 8-bit/pixel"},
    {BI_RLE4, "RLE 4-bit/pixel"},
    {BI_BITFIELDS, "Huffman 1D"},
    {BI_JPEG, "JPEG image for printing"},
    {BI_PNG, "PNG image for printing"},
    {BI_ALPHABITFIELDS, "RGBA bit field masks"},
    {BI_CMYK, "None"},
    {BI_CMYKRLE8, "RLE-8"},
    {BI_CMYKRLE4, "RLE-4"},
};

#if _WIN32
    #pragma pack(push, 1)
#endif
    typedef struct BitmapHeader
    {
        char headerField[2];
        unsigned int bitmapSize;
        char reserved[4];
        unsigned int offset;
        unsigned int headerSize;
        int bitmapWidth;
        int bitmapHeight;
        unsigned short colorPlaneCount;
        unsigned short bitsPerPixel;
        unsigned int compressionMethod;
        unsigned int imageSize;
        int horizontalResolution;
        int verticalResolution;
        unsigned int colorPaletteColorCount;
        unsigned int importantColors;        
    }
#if __APPLE__ 
    __attribute__((packed)) BitmapHeader;
#elif _WIN32
    BitmapHeader;
    #pragma pack(pop)
#endif
    
#endif