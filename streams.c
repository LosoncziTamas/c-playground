#include <stdio.h>

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

    // Sets the position indicator associated with the stream to a new position.
    // Second parameter is the offset, third is the origin. Returns zero on success.
    int result = fseek(fp, 0, SEEK_END);

    // Returns the current value of the position indicator of the stream.
    long size = ftell(fp);

    // Reset position indicator
    rewind(fp);
    long start = ftell(fp);

    fclose(fp);

    return 0;
}