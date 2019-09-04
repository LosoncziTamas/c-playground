#include <stdio.h>
#include "../../utils/loso_utils.c"

/*
    Pointer version of strcat.
*/

void AppendString(char* strA, const char* strB)
{
    while (*(++strA));
    while (*(strA++) = *(strB++));
    *strA = '\0';
}

int main()
{
    char strA[10] = "alma";
    char strB[5] = "1234";
    AppendString(strA, strB);
    assert(StringsAreEqual(strA, "alma1234"));
}

