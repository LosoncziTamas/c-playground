#ifndef COMMON_H
#define COMMON_H

#define ArrayCount(x) (sizeof(x) / sizeof(x[0]))
#define STREAM_SIZE 100

typedef enum
{
    Console,
    Memory
} StreamType;

typedef struct 
{
    char data[STREAM_SIZE];
    int datap;
    StreamType type;
} Stream;

void SetStream(Stream* stream);
int GetChar();
void UngetChar(int c);

#endif