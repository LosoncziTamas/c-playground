#include <stdio.h>
#include <ctype.h>
#include "../../utils/loso_utils.c"

int32 GetLine(char *s, int32 lim)
{
    int32 c;
    const char* start = s;
    --lim;

    while (lim-- && (c = GetChar()) != EOF && c != '\n')
    {
        *(s++) = c;
    }
    if (c == '\n')
    {
        *(s++) = c;
    }
    *s = '\0';

    return s - start;
}

int32 StringToInt32(char *s)
{
    int32 result = 0;

    for (; isspace(*s); s++);
    int32 sign = *s == '-' ? -1 : 1;
    if (*s == '-' || *s == '+') 
    {
        s++;
    }

    while (*s >= '0' && *s <= '9')
    {
        result = 10 * result + (*s - '0');
        s++;
    }

    return sign * result;
}

void ReverseString(char *str)
{
    uint32 len = StringLength(str);
    char *head = str;
    char *rear = str + len;
    
    char tmp = *str;
    
}


void TestGetLine()
{
    char buf[11];
    int32 len = GetLine(buf, 11);
    PrintInteger(len);
    PrintCharArray(buf, 10);
}

void TestStringToInt32()
{
    assert(12345 == StringToInt32("12345"));
    assert(12345 == StringToInt32("012345"));
    assert(-12345 == StringToInt32("-12345"));

}

int main()
{ 
    TestStringToInt32();
}