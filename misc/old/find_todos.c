#include "loso_utils.c"

#define CHUNK_SIZE 128

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
    int charBuff[CHUNK_SIZE];
    int readCharCount = 0;
    int lineCounter = 1;
    bool activeLineComment = false;
    bool activeBlockComment = false;
    
    //TODO: iterate over folder elements
    //TODO: consider when TODO is at halfway
    while ((readCharCount = ReadByChunk(charBuff, CHUNK_SIZE)))
    {
        for (int i = 0; i < readCharCount; ++i)
        {
            if (charBuff[i] == '\n')
            {
                lineCounter++;
                activeLineComment = false;
            }
            if (charBuff[i] == '/')
            {
                activeLineComment = !activeBlockComment && (i + 1 < readCharCount) && charBuff[i + 1] == '/';
                printf("activeLineComment %d line: %d\n", activeLineComment, lineCounter);
            }
            if (activeLineComment || activeBlockComment)
            {
                if (charBuff[i] == 'T' && i + 3 < readCharCount)
                {
                    if (charBuff[i + 1] == 'O' && charBuff[i + 2] == 'D' && charBuff[i + 3] == 'O')
                    {
                        // file name and path
                        printf("TODO at line: %d\n", lineCounter);
                    }
                }
            }
        }
    }

    return 0;
}