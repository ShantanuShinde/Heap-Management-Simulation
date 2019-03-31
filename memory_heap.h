#include "List.h"



void Initialization();

// Different types of allocations
void * FirstFit(int size);
void *NextFit(int size);
void * BestFit(int size);

void *Malloc(int size,int fitType);
void Free(void *pointer);

void PrintFreeList();
void PrintAllocList();
