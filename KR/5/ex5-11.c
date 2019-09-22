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

void Entab(uint32 tabWidth)
{
    for(int c = getchar(), blankCount = 0, charPerLine = 0; c != EOF; c = getchar())
    {
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
            putchar(c);
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

void ReadFile()
{
    //TODO: read file
}

int main(int argCount, char **args)
{
    ParsedArgs parsedArgs = {0};
    
    if (ParseArgs(argCount, args, &parsedArgs) > 0)
    {
        PrintText(parsedArgs.fileName);
        PrintIntegerArray(parsedArgs.tabStops, parsedArgs.tabStopCount);

    }
    else
    {
        PrintText(parsedArgs.message);
        PrintText("Usage: <filename> <tabstop1> <tabstop2> ...");
    }
}
