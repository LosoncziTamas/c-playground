#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define ArrayCount(x) (sizeof(x) / sizeof(x[0]))

#define BLACK   "\x1b[30m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define WHITE   "\x1b[97m"
#define COLOR_RESET   "\x1b[0m"

#define DIM_X 16
#define DIM_Y 16

typedef struct Console
{
    char content[DIM_X][DIM_Y];
} Console;

void ClearConsole()
{
#ifdef _WIN32
    system("clear");
#elif __APPLE__
    system("cls");
#endif
}

void SetColor(Console *console, int row, int column, int color)
{
    assert(row > 0 && column > 0);
    console->content[row][column] = color;
}



void PrintConsole(Console *console)
{
    for (int rowIndex = 0; rowIndex < ArrayCount(console->content); ++rowIndex)
    {
        for (int columnIndex = 0; columnIndex < ArrayCount(console->content[0]); ++columnIndex)
        {
            int color = console->content[rowIndex][columnIndex];
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

        }
    }
}