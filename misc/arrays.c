#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

void Reverse(int arr[], int size)
{
    for (int i = 0; i < size / 2; ++i)
    {
        int tmp = arr[i];
        arr[i] = arr[size - i - 1];
        arr[size - i - 1] = tmp;
    }
}

bool SameContent(int a1[], int a2[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        if (a1[i] != a2[i])
        {
            return false;
        } 
    }
    return true;
}

void PrintArray(int a[], int size)
{
    for(int i = 0; i < size; ++i)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void LeftShift(int a1[], int size)
{
    for (int i = 0; i < size - 1; ++i)
    {
        int newPos = i > 0 ? i - 1 : size - 1;
        int temp = a1[newPos];
        a1[newPos] = a1[i];
        a1[i] = temp;
    }
}

/*
    Returns number of pairs which add up to the provided value.
*/
int FindPairs(int a[], int size, int val)
{
    int result = 0;
    for (int i = 0; i < size; ++i)
    {
        for (int j = i + 1; j < size; ++j)
        {
            if (a[i] + a[j] == val) 
            {
                result++;
            }
        }
    }
    return result;
}

int main()
{
    int a1[] = {1, 2, 3, 4, 5};
    int size = sizeof(a1) / sizeof(a1[0]);

    {
        Reverse(a1, size);
        int expected[] = {5, 4, 3, 2, 1};
        assert(SameContent(a1, expected, size));
    }

    {
        LeftShift(a1, size);
        int expected[] = {4, 3, 2, 1, 5};
        assert(SameContent(a1, expected, size));
    }

    {
        int pairCount = FindPairs(a1, size, 5);
        assert(pairCount == 2);
    }

}