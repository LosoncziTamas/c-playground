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

void TestGetLine()
{
    char buf[11];
    int32 len = GetLine(buf, 11);
    PrintInteger(len);
    PrintCharArray(buf, 10);
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

void TestStringToInt32()
{
    assert(12345 == StringToInt32("12345"));
    assert(12345 == StringToInt32("012345"));
    assert(-12345 == StringToInt32("-12345"));
}

void ReverseString(char *str)
{
    uint32 len = StringLength(str);
    char *start = str;
    char *end = str + len - 1;
    
    while (end - start > 0)
    {
        char tmp = *start;
        *(start++) = *end;
        *(end--) = tmp;
    }
}

void TestReverseString()
{
    {
        char str[10] = "almafa";
        ReverseString(str);
        assert(StringsAreEqual("afamla", str));
    }
    {
        char str[10] = "123";
        ReverseString(str);
        assert(StringsAreEqual("321", str));
    }
        {
        char str[10] = "a";
        ReverseString(str);
        assert(StringsAreEqual("a", str));
    }
}

void Int32ToString(int32 n, char* s)
{
    int32 sign = n;
    char *start = s;

    if (sign < 0)
    {
        //TODO: fix largest negative number
        n = -n;
    }

    do
    {
        *(s++) = n % 10 + '0';
    } 
    while ((n /= 10) > 0);

    if (sign < 0)
    {
        *(s++) = '-';
    }
    *s = '\0';

    ReverseString(start);
}

void TestInt32ToString()
{
    {
        int32 n = 12345;
        char s[10] = {0};   
        Int32ToString(n, s);
        assert(StringsAreEqual(s, "12345"));
    }
    {
        int32 n = 1;
        char s[10] = {0};   
        Int32ToString(n, s);
        assert(StringsAreEqual(s, "1"));
    }
}

int main()
{ 
    // TestGetLine();
    // TestReverseString();
    // TestStringToInt32();
    // TestInt32ToString();
}