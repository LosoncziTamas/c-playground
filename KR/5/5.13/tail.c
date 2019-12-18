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

    // Expected usage: tail <text>
    if (argc == 2)
    {
        char *endP = NULL;
        int tail = strtol(argv[1], &endP, 10);

        if (tail == 0L)
        {
            printf("Passed text %s", argv[1]);
            parsedArgs->length = strlen(argv[1]);
            parsedArgs->text = GetMemory(parsedArgs->length + 1);
            strcpy(parsedArgs->text, argv[1]);
            parsedArgs->tail = 10;

            success = true;
        }
        // Covering the case when text starts with number.
        else if (endP && strlen(endP) > 0)
        {
            printf("Text starts with number %s", argv[1]);

            success = true;
        }
    }
    else if (argc == 3)
    {

        success = true;
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