#include "../../utils/loso_utils.c"

#define TAB_WIDTH 8
#define MAX_TABSTOP 2
#define FILENAME_LEN 64
#define MESSAGE_LEN 64
#define TAB_ARGS_START_INDEX 2

void PrintBlanksOptimally(int blankCount, int blankStart)
{
    int toNextStop = TAB_WIDTH - (blankStart % TAB_WIDTH);

    // move to next tab stop
    if (blankCount >= toNextStop)
    {
        putchar('\t');
        blankCount -= toNextStop;
    }

    int tabCount = blankCount / TAB_WIDTH;
    int spaceCount = blankCount % TAB_WIDTH;

    for (int i = 0; i < tabCount; ++i)
    {
        putchar('\t');
    }
    for (int i = 0; i < spaceCount; ++i)
    {
        putchar(' ');
    }
}

void Entab(uint32 tabWidth, const char* source, uint32 sourceLength, char* dest, uint32 destLength)
{
    uint32 blankCount = 0;
    uint32 charPerLine = 0;

    for(uint32 charIndex = 0; charIndex < sourceLength; ++charIndex)
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
                PrintBlanksOptimally(blankCount, charPerLine - blankCount);
                blankCount = 0;
            }
            *(dest++) = c;
            //TODO: check dest bounds
            charPerLine = c == '\n' ? 0 : charPerLine + 1;
        }
    }
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

        PrintInteger(argCount);
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
        if (writeCount == sourceLength)
        {
            return writeCount;
        }
        return -1;
    }
    return -1;
}

int main(int argCount, char **args)
{
    ParsedArgs parsedArgs = {0};
    char fileContent[1024] = {0};
    char writeBuffer[1024] = {0};
    
    if (ParseArgs(argCount, args, &parsedArgs) > 0)
    {
        ReadFile(parsedArgs.fileName, fileContent, ArrayCount(fileContent));
        Entab(parsedArgs.tabStops[0], fileContent, ArrayCount(fileContent), writeBuffer, ArrayCount(writeBuffer));
        WriteFile("output", writeBuffer, ArrayCount(writeBuffer));
    }
    else
    {
        PrintText(parsedArgs.message);
        PrintText("Usage: <filename> <tabstop1> <tabstop2> ...");
    }
}
