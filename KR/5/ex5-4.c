#include <stdio.h>
#include "../../utils/loso_utils.c"

int32 StringEnd(const char* str, const char* t)
{
    uint32 strLen = StringLength(str);
    uint32 tLen = StringLength(t);
    if (tLen > strLen) 
    {
        return 0;
    } 

    const char *start = str + (strLen - tLen);
    while (*start == *t && *start != '\0')
    {
        start++;
        t++;
    }
    return *start == '\0';
}

int main()
{
    assert(StringEnd("alma1234", "1234"));
    assert(!StringEnd("alma1234", "123"));
    assert(StringEnd("", ""));
}