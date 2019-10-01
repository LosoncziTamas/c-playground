#include "../../utils/loso_utils.c"

#define TAB_WIDTH 8
#define MAX_TABSTOP 2
#define FILENAME_LEN 64
#define MESSAGE_LEN 64
#define TAB_ARGS_START_INDEX 2

typedef enum ErrorCode
{
    SUCCESS = 0,
    FILE_LOAD_ERROR = -1
} ErrorCode;

struct ErrorDesc
{
    ErrorCode err;
    const char* desc;
} errorDesc [] = 
{
    {SUCCESS, ""}
};

uint32 WriteBlanks(int blankCount, int blankStart, char* dest)
{
    uint32 writtenCount = 0;
    uint32 toNextStop = TAB_WIDTH - (blankStart % TAB_WIDTH);

    // Move to next tab stop.
    if (blankCount >= toNextStop)
    {
        *(dest++) = '\t';
        blankCount -= toNextStop;
        writtenCount++;
    }

    uint32 tabCount = blankCount / TAB_WIDTH;
    uint32 spaceCount = blankCount % TAB_WIDTH;

    for (uint32 i = 0; i < tabCount; ++i)
    {
        *(dest++) = '\t';
    }
    for (uint32 i = 0; i < spaceCount; ++i)
    {
        *(dest++) = ' ';
    }
    writtenCount += tabCount + spaceCount;

    return writtenCount;
}

int32 Entab(uint32 tabWidth, const char* source, uint32 sourceLength, char* dest)
{
    uint32 blankCount = 0;
    uint32 charPerLine = 0;
    const char* destStart = dest;

    for (uint32 charIndex = 0; charIndex < sourceLength; ++charIndex)
    {
        char c = *(source + charIndex);
        if (c == ' ')
        {
            blankCount++;
            charPerLine++;
        }
        else if (c == '\t')
        {
            int toNextStop = TAB_WIDTH - (charPerLine % TAB_WIDTH);
            blankCount += toNextStop;
            charPerLine += toNextStop;
        }
        else
        {
            if (blankCount > 0)
            {
                WriteBlanks(blankCount, charPerLine - blankCount, dest);
                blankCount = 0;
                dest++;
            }
            *(dest++) = c;
            charPerLine = c == '\n' ? 0 : charPerLine + 1;
        }
    }

    return dest - destStart;
}

typedef struct ParsedArgs
{
    uint32 tabStopCount;
    uint32 tabStops[MAX_TABSTOP];
    char fileName[FILENAME_LEN];
    char message[MESSAGE_LEN];
} ParsedArgs;

int32 StringToInt32(const char* string)
{
    int32 result = atoi(string);
    return result;
}

int32 ParseArgs(int argCount, char **args, ParsedArgs *parsedArgs)
{
    if (argCount > 1)
    {
        char* fileName = args[1];
        if (StringLength(fileName) < FILENAME_LEN)
        {
            CopyString(parsedArgs->fileName, fileName);
        }
        else
        {
            CopyString(parsedArgs->message, "Invalid filename.");
            return -1;
        }

        if (argCount - TAB_ARGS_START_INDEX <= MAX_TABSTOP)
        {
            uint32 argIndex;
            for (argIndex = TAB_ARGS_START_INDEX; argIndex < argCount; ++argIndex)
            {
                int32 tabStop = StringToInt32(args[argIndex]);
                if (tabStop > 0) 
                {
                    parsedArgs->tabStops[argIndex - TAB_ARGS_START_INDEX] = tabStop;
                }
                else
                {
                    CopyString(parsedArgs->message, "Invalid tab stop value.");
                    return -1;
                }
            }
            parsedArgs->tabStopCount = argCount - TAB_ARGS_START_INDEX;
        }
        else
        {
            CopyString(parsedArgs->message, "Invalid tab stop count.");
            return -1;
        }
    }
    else
    {
        CopyString(parsedArgs->message, "Invalid argument count.");
        return -1;
    }

    PrintInteger(parsedArgs->tabStopCount);
    return parsedArgs->tabStopCount;
}

int32 ReadFile(const char* fileName, char* dest, uint32 destLength)
{
    FILE* file = fopen(fileName, "r");
    if (file)
    {
        if (fseek(file, 0, SEEK_END) == 0)
        {
            int32 contentLength = ftell(file);
            if (contentLength > 0)
            {   
                rewind(file);
                if (destLength < contentLength)
                {
                    return - 1;
                }
                int32 readSize = fread(dest, sizeof(char), contentLength, file);
                fclose(file);
                if (readSize == contentLength)
                {
                    return readSize;
                }
            }
        }
    }
    return -1;
}

int32 WriteFile(const char* fileName, const char* source, uint32 sourceLength)
{
    FILE* fileToWrite = fopen(fileName, "w");
    if (fileToWrite)
    {
        uint32 writeCount = fwrite(source, sizeof(char), sourceLength, fileToWrite);
        fclose(fileToWrite);
        PrintInteger(writeCount);
        if (writeCount == sourceLength)
        {
            return writeCount;
        }
        return -1;
    }
    return -1;
}

bool SameFileContent(const char* fileA, const char* fileB)
{
    char buffA[1024] = {0};
    char buffB[1024] = {0};
    int32 aLen = ReadFile(fileA, buffA, ArrayCount(buffA));
    int32 bLen = ReadFile(fileB, buffB, ArrayCount(buffB));

    if (aLen > 0 && aLen == bLen)
    {
        for (uint32 byteIndex = 0; byteIndex < aLen; ++byteIndex)
        {
            if (buffA[byteIndex] != buffB[byteIndex])
            {
                return false;
            }
        }
        return true;
    }

    return false;
}

// TODO: util for printing error/assertion, using console coloring
int main(int argCount, char **args)
{
    const char* outputName = "output.txt";
    ParsedArgs parsedArgs = {0};
    
    if (ParseArgs(argCount, args, &parsedArgs) > 0)
    {
        char readBuffer[1024] = {0};
        char writeBuffer[1024] = {0};
        int32 contentLength = ReadFile(parsedArgs.fileName, readBuffer, ArrayCount(readBuffer));

        if (contentLength > 0 && contentLength < ArrayCount(writeBuffer))
        {
            int32 destLen = Entab(parsedArgs.tabStops[0], readBuffer, contentLength, writeBuffer);
            WriteFile(outputName, writeBuffer, destLen);
            if (SameFileContent(outputName, parsedArgs.fileName))
            {
                PrintText("Same file");
            }
            else
            {
                PrintText("Different files");
            }
        }
        else
        {
            PrintText("Buffer size is too small");
        }
    }
    else
    {
        PrintText(parsedArgs.message);
        PrintText("Usage: <filename> <tabstop1> <tabstop2> ...");
    }
}
