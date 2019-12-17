#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define ArrayLength(x) (sizeof(x) / sizeof(x[0]))
#define MAX_MEM 2048

static char AppMemory[MAX_MEM];
static int MemP = 0;

typedef struct 
{
    const char* text;
    int length;
    int lineCount;
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
    char* strB = GetMemory(strlen(strA));

    if (strB)
    {
        strcpy(strB, strA);
        
    }
}

bool ReadArgs(ParsedArgs *parsedArgs)
{

    return false; 
}

int main(int argc, char ** argv)
{
    ParsedArgs args = {0};

    if (ReadArgs(&args))
    {
        
    }
    else 
    {
        printf("Invalid parameters. Usage: tail -n <text>");
        exit(1);
    }

    return 0;
}