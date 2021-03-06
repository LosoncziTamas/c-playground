#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>

#define ArrayLength(x) (sizeof(x) / sizeof(x[0]))
#define MAX_MEM 2048
#define DEFAULT_TAIL 10

static char AppMemory[MAX_MEM];
static int MemP = 0;

typedef struct 
{
    int tail;
    char* text;
    int length;
} ParsedArgs;

char* GetMemory(size_t size)
{
    char* result = NULL;

    if (MemP + size < ArrayLength(AppMemory))
    {
        result = AppMemory + MemP;
        MemP += size;
    }

    return result;
}

void PrintArgs(ParsedArgs* args)
{
    if (args)
    {
        if (args->text)
        {
            printf("Tail: %d, text: %s, length: %d.\n", args->tail, args->text, args->length);
        }
        else 
        {
            printf("Tail: %d, length: %d.\n", args->tail, args->length);
        }
    }
}

bool ParseTextArg(const char* textArg, ParsedArgs *parsedArgs)
{
    char *endP = NULL;
    bool alphabetic = strtol(textArg, &endP, 10) == 0L;
    bool startsWithNumber = endP && strlen(endP) > 0;

    if (alphabetic || startsWithNumber)
    {
        int len = strlen(textArg);
        parsedArgs->length = len;
        parsedArgs->text = GetMemory(len + 1);
        strcpy(parsedArgs->text, textArg);
        parsedArgs->text[len] = '\0';

        return true;
    }

    return false;
}

bool ReadArgs(int argc, char ** argv, ParsedArgs *parsedArgs)
{
    bool success = false;

    if (argc == 2 && ParseTextArg(argv[1], parsedArgs))
    {
        parsedArgs->tail = DEFAULT_TAIL;
        success = true;
    }
    else if (argc == 3)
    {
        bool prefixed = *argv[1] == '-';
        int tailValue = 0;

        if (prefixed && strlen(argv[1]) > 1)
        {
            tailValue = strtol(argv[1] + 1, NULL, 10);
        }
        else
        {
            tailValue = strtol(argv[1], NULL, 10);
        }

        if (tailValue > 0 && ParseTextArg(argv[2], parsedArgs))
        {
            parsedArgs->tail = tailValue;
            success = true;
        }
    }

    return success; 
}

int Max(int x, int y)
{
    return x > y ? x : y;
}

int main(int argc, char ** argv)
{
    ParsedArgs args = {0};

    if (ReadArgs(argc, argv, &args))
    {
        int end = args.length - 1;

        char** reversedLines = GetMemory(sizeof(char *) * args.tail);
        int lineCounter = 0;

        // TODO add case for single line
        // TODO add case for starting with new line char
        for (int i = end; i >= 0; --i)
        {
            bool printLine = args.text[i] == '\n' && i != end && args.tail > lineCounter;
            if (printLine) 
            {
                int lineLength = end - i;
                char *line = GetMemory(lineLength + 1);

                // Copy after the new line char
                memcpy(line, &args.text[i + 1], lineLength);
                line[lineLength] = '\0';
                reversedLines[lineCounter] = line;

                lineCounter++;
                end = Max(i - 1, 0);
            }
        }

        for (int i = lineCounter - 1; i >= 0; --i) 
        {
            printf("%s \n", reversedLines[i]);
        }
    }
    else 
    {
        PrintArgs(&args);
        printf("Invalid parameters. Usage: tail -n <text>");
        exit(1);
    }

    return 0;
}