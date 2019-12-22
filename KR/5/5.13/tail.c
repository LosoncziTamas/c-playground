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

void TestGetMemory()
{
    const char* strA= "Sample text";
    int len = strlen(strA);
    char* strB = GetMemory(len + 1);

    if (strB)
    {
        strcpy(strB, strA);
        *(strB + len) = '\0';
        printf("%s", strB);
    }
    else 
    {
        printf("Not enough memory.");
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

void PrintSubString(const char* str, int start, int end)
{
    assert(start <= end);
    for (char c = 0; start <= end; ++start)
    {
        c = *(str + start);
        putchar(c);
    }
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
        int lineCounter = 0;
        int end = args.length;

        // TODO: reverse
        // char** reversedTail = GetMemory(sizeof(char *) * args.tail);

        for (int i = end; i >= 0; --i)
        {
            bool printLine = args.text[i] == '\n' && i != end && args.tail > lineCounter;
            if (printLine)
            {

                PrintSubString(args.text, i + 1, end);
                putchar('\n');
                ++lineCounter;
                end = Max(i - 1, 0);
            }
        }
        // Printing last remainder line
        if (args.tail > lineCounter)
        {
            PrintSubString(args.text, 0, end);
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