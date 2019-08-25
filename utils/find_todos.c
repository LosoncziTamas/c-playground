#include "loso_utils.c"

int ReadByChunk(int chunk[], int chunkSize)
{
    int c, readCharCount = 0;

    for (c = getchar(); c != EOF && readCharCount < chunkSize; c = getchar())
    {
        chunk[readCharCount] = c;
        ++readCharCount;
    }

    return readCharCount;
}

int main(int argc, char** argv)
{
    int charBuff[128];
    int readCharCount = 0;
    int lineCounter = 0;

    while (readCharCount = ReadByChunk(charBuff, 128))
    {
        for (int i = 0; i < readCharCount; ++i)
        {
            if (charBuff[i] == '\n')
            {
                lineCounter++;
            }
            if (charBuff[i] == 'T' && i + 3 < readCharCount)
            {
                if (charBuff[i + 1] == 'O' && charBuff[i + 2] == 'D' && charBuff[i + 3] == 'O')
                {
                    printf("TODO at line: %d\n", lineCounter);
                }
            }
        }
    }

    return 0;
}