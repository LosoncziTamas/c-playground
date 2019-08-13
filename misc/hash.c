#include <stdio.h>

typedef struct Entry 
{
    int data;
} Entry;

typedef struct Hash 
{
    int index;
    Entry* ptr;
} Hash;

Hash* GetHashFromIndex(Hash* hash, int index, int arrayCount)
{
    Hash* result = 0;
    
    int hashValue = index;
    for (int i = 0; i < arrayCount; ++i)
    {
        int hashMask = arrayCount - 1;
        int hashIndex = (hashValue + i) & hashMask;
        Hash* entry = hash + hashIndex;
        if ((entry->index == 0) || (entry->index == index))
        {
            result = entry;
        }
    }

    return result;
}

int main() 
{
    Hash hash[64];

}
