#include "../../utils/loso_utils.c"

#define TAB_WIDTH 8
#define COLUMN_COUNT 5

void PrintBlanksOptimally(int blankCount, int blankStart)
{
    int toNextStop = TAB_WIDTH - (blankStart % TAB_WIDTH);

    // move to next tab stop
    if (blankCount >= toNextStop)
    {
        putchar('\t');
        blankCount -= toNextStop;
    }

    int tabCount = blankCount / TAB_WIDTH;
    int spaceCount = blankCount % TAB_WIDTH;

    for (int i = 0; i < tabCount; ++i)
    {
        putchar('\t');
    }
    for (int i = 0; i < spaceCount; ++i)
    {
        putchar(' ');
    }
}

void Entab()
{
    for(int c = getchar(), blankCount = 0, charPerLine = 0; c != EOF; c = getchar())
    {
        if (c == ' ')
        {
            blankCount++;
            charPerLine++;
        }
        else if (c == '\t')
        {
            int toNextStop = TAB_WIDTH - (charPerLine % TAB_WIDTH);
            blankCount += toNextStop;
            charPerLine += toNextStop;
        }
        else
        {
            if (blankCount > 0)
            {
                PrintBlanksOptimally(blankCount, charPerLine - blankCount);
                blankCount = 0;
            }
            putchar(c);
            charPerLine = c == '\n' ? 0 : charPerLine + 1;
        }
    }
}

int main(int argCount, char **args)
{
    Entab();
}
