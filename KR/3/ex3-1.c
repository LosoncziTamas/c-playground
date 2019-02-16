
/*  Our binary search makes two 
    tests inside the loop, when 
    one would suffice (at the 
    price of more tests outside). 
    Write a version with only one
    test inside the loop and measure
    the difference in run-time. */

int binsearch(int x, int v[], int len)
{
    for(int high = len - 1, low = 0; low <= high;)
    {
        int mid = (low + high) / 2;
        if (v[mid] > x)
        {
            high = mid - 1;
        }
        else if (v[mid] < x)
        {
            low = mid + 1;
        }
        else 
        {
            return mid;
        }
    }
    return -1;
}

int main()
{
    int v[] = {1, 20, 33, 67, 100, 203, 500, 667, 987};
    int result = binsearch(987, v, 9);

    return 0;
}