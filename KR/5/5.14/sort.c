#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define MAXLEN 1000
#define MAXLINES 5000

char* lines[MAXLINES];

char* Alloc(int size)
{
    assert(size >= 0);
    char* result = (char*) malloc(size);
    return result;
}

int GetLine(char* dest, int max)
{
    assert(dest);
    const char* start = dest;

    for (int c = getchar(); c != EOF && c != '\n' && max > 0; c = getchar())
    {
        --max;
        *(dest++) = c;
    }
    *dest = '\0';

    return dest - start;
}

int ReadLines(char* linePtr[], int maxLines)
{
    char line[MAXLEN];
    int lineCount = 0;

    for (int len = GetLine(line, MAXLEN); len > 0; len = GetLine(line, MAXLEN))
    {
        char* p = Alloc(len);
        if (lineCount >= maxLines || p == NULL)
        {
            return -1;
        }
        else
        {
            line[len] = '\0';
            strcpy(p, line);
            linePtr[lineCount++] = p;
        }
    }

    return lineCount;
}

void WriteLines(char* linePtr[], int lineCount)
{
    for (int i = 0; i < lineCount; ++i)
    {
        printf("%s\n", linePtr[i]);
    }
}

int NumberComparator(char* s1, char* s2)
{
    double a = atof(s1);
    double b = atof(s2);

    return a < b ? -1 : (a > b ? 1 : 0);
}

int ReverseNumberComparator(char* s1, char* s2)
{
    return NumberComparator(s2, s1);
}

int StringComparator(char* s1, char* s2)
{
    return strcmp(s1, s2);
}

int ReverseStringComparator(char* s1, char* s2)
{
    return strcmp(s2, s1);
}

void Swap(char* v[], int i, int j)
{
    void* temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void QuickSort(char *data[], int left, int right, int (*comparator)(char*, char*))
{
    if (left >= right)
    {
        return;
    }
    Swap(data, left, (left + right) / 2);
    int last = left;
    for (int i = left + 1; i <= right; ++i)
    {
        if (comparator(data[i], data[left]) < 0)
        {
            Swap(data, ++last, i);
        }
    }
    Swap(data, left, last);
    QuickSort(data, left, last - 1, comparator);
    QuickSort(data, last + 1, right, comparator);
}

int main(int argc, char* argv[])
{
    bool isNumeric = false;
    bool reverse = false;

    if (argc == 2)
    {
        isNumeric = strcmp(argv[1], "-n") == 0;
        reverse = strcmp(argv[1], "-r") == 0;
    } 
    else if (argc == 3)
    {
        isNumeric = strcmp(argv[1], "-n") == 0 || strcmp(argv[2], "-n") == 0;
        reverse = strcmp(argv[1], "-r") == 0 || strcmp(argv[2], "-r") == 0;
    }

    int lineCount = ReadLines(lines, MAXLINES);

    if (lineCount > 0)
    {
        if (isNumeric)
        {
            QuickSort(lines, 0, lineCount - 1, reverse ? ReverseNumberComparator : NumberComparator);
        }
        else
        {
            QuickSort(lines, 0, lineCount - 1, reverse ? ReverseStringComparator : StringComparator);
        }
        WriteLines(lines, lineCount);
        return 0;
    }

    printf(lineCount == 0 ? "No input to sort.\n" : "Input too big to sort.\n");
    
    return 1;
}