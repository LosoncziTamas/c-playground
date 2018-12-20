#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

long getFileSize(FILE *fp)
{
    long result = 0;
    // Sets the position indicator associated with the stream to a new position.
    // Second parameter is the offset, third is the origin. Returns zero on success.
    if (fseek(fp, 0, SEEK_END) == 0)
    {
        // Returns the current value of the position indicator (number of characters from the beginning) of the stream
        result = ftell(fp);
    }
    // Reset position indicator
    rewind(fp);
    return result;
}

int main(void)
{

    // The second parameter defines the access mode.
    // To read a file in binary mode append b to the mode string.
    // Some special character conversion may occur in input/output operations in text mode to adapt them to a system-specific text file format.
    // Generally want to use binary mode
    FILE *fp = fopen("testfile.txt", "rb");
    if (fp)
    {
        fprintf(stdout, "File opened");
    }
    else
    {
        fprintf(stderr, "Couldn't open file");
        return 1;
    }

    long size = getFileSize(fp);
    assert(size > 0);
    char *buff = malloc(size * sizeof(char));
    // This also advances the file position indicator
    size_t elementsRead = fread(buff, sizeof(char), size, fp);

    fclose(fp);
    free(buff);

    return 0;
}