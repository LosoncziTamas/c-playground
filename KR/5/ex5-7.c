#include "../../utils/loso_utils.c"

#define MAXLINES 5000

static char *lines[MAXLINES];

int32 ReadLines(char **dest, uint32 maxLines);
void WriteLines(char **source, uint32 lineCount);
void QuickSort(char **source, uint32 left, uint32 right);

int main()
{
    int32 lineCount = 0;

    if ((lineCount = ReadLines(lines, MAXLINES)) >= 0)
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