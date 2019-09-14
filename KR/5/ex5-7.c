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
        if (lineCount < maxLines && arrLen - arrP > lineLength)
        {
            char *p = arr + arrP;
            arrP += lineLength;
            // line[lineLength - 1] = '\0';
            CopyString(p, line);
            *(dest + lineCount) = p;
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
    while(lineCount > 0)
    {
        PrintText(*(source + lineCount));
        lineCount--;
    }
}

void QuickSort(char **source, uint32 left, uint32 right)
{

}

int main()
{
    /*char buff[100] = {0};
    char buff2[100] = {0};
    while (GetLine(buff, 100) > 0)
    {
        CopyString(buff2, buff);
        PrintText(buff2);

    }*/
    char arr[100];
    int32 lineCount = 0;

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