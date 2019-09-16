#include "../../utils/loso_utils.c"

#define MAXLINES 5000
#define MAXLEN 1000

static char *lines[MAXLINES];

uint32 GetLine(char* line, uint32 len)
{
    uint32 charCount = 0;
    int32 c;

    while ((c = GetChar()) != EOF && c != '\n')
    {
        if (len - 1 > charCount)
        {
            *(line + charCount) = c; 
            charCount++;
        }
        else 
        {
            return -1;
        }
    }
    *(line + charCount) = '\0';

    return charCount;
}

void CopyString(char* dest, const char* source)
{
    while (*source)
    {
        *(dest++) = *(source++);
    }
    *dest = '\0';
}

int32 ReadLines(char **dest, uint32 maxLines, char* arr, int32 arrLen)
{
    char line[MAXLEN] = {0};
    int32 lineCount = 0;
    int32 lineLength = 0;
    int32 arrP = 0;

    while ((lineLength = GetLine(line, MAXLEN)) > 0)
    {
        if (lineCount < maxLines && arrLen - arrP > lineLength + 1)
        {
            char *p = arr + arrP;
            arrP += lineLength + 1;
            CopyString(p, line);
            dest[lineCount] = p;
            ++lineCount;
        }
        else
        {
            return -1;
        }
    }

    return lineCount;
}

void WriteLines(char **source, uint32 lineCount)
{
    for (uint32 i = 0; i < lineCount; ++i)
    {
        PrintText(source[i]);
    }
}

void QuickSort(char **source, uint32 left, uint32 right)
{
    //TODO: implement sorting
}

int main()
{
    char arr[100];
    int32 lineCount = 0;

    //TODO: measure performance and compare
    if ((lineCount = ReadLines(lines, MAXLINES, arr, 100)) >= 0)
    {
        QuickSort(lines, 0, lineCount - 1);
        WriteLines(lines, lineCount);
        return 0;
    }
    else
    {
        PrintText("Error: input too big to sort.");
        return 1;
    }

}