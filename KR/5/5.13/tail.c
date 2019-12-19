#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define ArrayLength(x) (sizeof(x) / sizeof(x[0]))
#define MAX_MEM 2048

static char AppMemory[MAX_MEM];
static int MemP = 0;

typedef struct 
{
    char* text;
    int length;
    int tail;
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

bool ReadArgs(int argc, char ** argv, ParsedArgs *parsedArgs)
{
    bool success = false;

    // tail <text>
    if (argc == 2)
    {
        char *endP = NULL;
        bool alphabetic = strtol(argv[1], &endP, 10) == 0L;
        bool startsWithNumber = endP && strlen(endP) > 0;

        if (alphabetic || startsWithNumber)
        {
            int len = strlen(argv[1]);
            parsedArgs->length = len;
            parsedArgs->text = GetMemory(len + 1);
            strcpy(parsedArgs->text, argv[1]);
            parsedArgs->text[len] = '\0';
            parsedArgs->tail = 10;

            success = true;
        }
    }
    // tail -n <text> 
    else if (argc == 3)
    {
        bool prefixed = *argv[1] == '-';
        int tailValue = prefixed;

        if (prefixed && strlen(argv[1]) > 1)
        {
            tailValue = strtol(argv[1] + 1, NULL, 10);
        }
        else
        {
            tailValue = strtol(argv[1], NULL, 10);
        }

        // Is the tail parameter valid?
        if (tailValue > 0)
        {
            printf("Valid tail value: %d", tailValue);
            success = true;
        }
    }

    return success; 
}

int main(int argc, char ** argv)
{
    ParsedArgs args = {0};

    if (ReadArgs(argc, argv, &args))
    {
        
    }
    else 
    {
        printf("Invalid parameters. Usage: tail -n <text>");
        exit(1);
    }

    return 0;
}