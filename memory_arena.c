#include <stdio.h>
#include <stdlib.h>

typedef struct MemoryArena 
{
    char* base;
    size_t size;
    size_t used;
} MemoryArena;

typedef struct AppState
{
    char c[64];
    int i[16];
    MemoryArena arena;
} AppState;

void initMemoryArena(MemoryArena* arena, size_t size, void* base) 
{
    arena->size = size;
    arena->base = (char*) base;
    arena->used = 0;
}

int main(void) 
{
    return 0;
}