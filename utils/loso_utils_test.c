#include "loso_utils.c"

void TestArrayCount()
{
    int array[100]; 
    assert(ArrayCount(array) == 100);

    struct Foo 
    {
        char a;
        char b;
    };
    struct Foo fooArray[50];
    assert(ArrayCount(fooArray) == 50);

    struct Bar
    {
        int a[20];
    };
    struct Bar bar;
    assert(ArrayCount(bar.a) == 20);
}

void TestIntSize()
{
    assert(sizeof(uint32) == 4);
    assert(sizeof(int32) == 4);
}

void TestStringLength()
{
    assert(StringLength("1234") == 4);
    assert(StringLength("") == 0);

    char string[100];
    uint32 max = 32;
    assert(StringLengthSafe(string, max) < max);
}

void TestStringsAreEqual()
{
    assert(StringsAreEqual("1 2 ", "1 2 "));
    assert(StringsAreEqual(" 1 2 ", " 1 2 "));
    assert(!StringsAreEqual("1 2 ", " 1 2  "));
    assert(!StringsAreEqual("  1 2 ", " 1 2"));
}

void TestStringConcat()
{
    char sourceA[] = "1234";
    char sourceB[] = "5678";
    char dest[10];

    StringConcat(sourceA, 4, sourceB, 4, dest, 10);
    assert(StringsAreEqual("12345678", dest));
}

int main(void) 
{
    TestArrayCount();
    TestIntSize();
    TestStringLength();
    TestStringConcat();
    TestStringsAreEqual();
}
