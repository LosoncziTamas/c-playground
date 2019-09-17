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

/*
    Interchange source[i] and source[j]
*/

void Swap(char** source, uint32 i, uint32 j)
{
    char* tmp = source[i];
    source[i] = source[j];
    source[j] = tmp;
}

int32 CompareString(const char* strA, const char* strB)
{
    int32 result = *strA - *strB;

    while (result == 0 && *strA && *strB)
    {
        result = *(++strA) - *(++strB);
    }

    return result;
}

void QuickSort(char **source, uint32 left, uint32 right)
{
    if (left >= right)
    {
        return;
    }
    uint32 last = left;
    Swap(source, left, (left + right) / 2);
    for (uint32 i = left + 1; i <= right; ++i)
    {
        if (CompareString(source[i], source[left]) < 0)
        {
            Swap(source, ++last, i);
        }
    }
    Swap(source, left, last);
    QuickSort(source, left, last);
    QuickSort(source, last + 1, right);
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