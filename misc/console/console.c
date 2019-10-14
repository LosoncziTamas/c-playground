#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define ArrayCount(x) (sizeof(x) / sizeof(x[0]))

#define BLUE    "\x1b[34m"
#define WHITE   "\x1b[97m"
#define COLOR_RESET   "\x1b[0m"

#define DIM_X 32
#define DIM_Y 32

typedef struct
{
    char content[DIM_X][DIM_Y];
} Console;

typedef enum
{
    BLACK   = 0,
    RED     = 1,
    GREEN   = 2,
    YELLOW  = 3
} ConsoleColor;

static const struct  
{
    ConsoleColor name;
    char value[6];
} 
ColorTable [4] = {
    {BLACK,     "\x1b[30m"},
    {RED,       "\x1b[31m"},
    {GREEN,     "\x1b[32m"},
    {YELLOW,    "\x1b[33m"},
};

void ClearConsole()
{
#ifdef _WIN32
    system("clear");
#elif __APPLE__
    system("cls");
#endif
}

void SetColor(Console *console, int row, int column, char colorIndex)
{
    assert(row > -1 && column > -1);
    console->content[row][column] = colorIndex;
}

void PrintConsole(Console *console)
{
    for (int rowIndex = 0; rowIndex < ArrayCount(console->content); ++rowIndex)
    {
        for (int columnIndex = 0; columnIndex < ArrayCount(console->content[0]); ++columnIndex)
        {
            char colorIndex = console->content[rowIndex][columnIndex];
            const char* color = ColorTable[colorIndex].value;
            printf( "%s 0" COLOR_RESET, color); 
        }
    }
}


int main()
{
    Console console = {0};

    assert(ArrayCount(console.content) == DIM_X);
    assert(ArrayCount(console.content[0]) == DIM_Y);

    for (int rowIndex = 0; rowIndex < ArrayCount(console.content); ++rowIndex)
    {
        for (int columnIndex = 0; columnIndex < ArrayCount(console.content[0]); ++columnIndex)
        {
            SetColor(&console, rowIndex, columnIndex, RED);
        }
    }

    // PrintConsole(&console);
    // TODO: Check on mac
    printf(BLUE "Blue text" COLOR_RESET);
}