#include<iostream>

#include "memory_heap.h"

using namespace std;

int main()
{
    
    Initialization();
    PrintFreeList();
    int *c = (int *)Malloc(sizeof(int)*20,2);
    int *b = (int *)Malloc(sizeof(int)*20,2);
    Free(c);
    PrintFreeList();
    PrintAllocList();

    return 0;
}



