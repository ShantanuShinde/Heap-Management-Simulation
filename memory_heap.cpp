#include "memory_heap.h"
#include<iostream>
#include<random>

using namespace std;

static char MEMORY[4096];

static int AVAILABLE_BLOCK_SIZES[9] = {4,8,16,32,64,128,256,512,1024};
static List *free_list = new List();
static List2 *alloc_list = new List2();


void Initialization()
{
    random_device rd;

    mt19937 eng(rd());

    uniform_int_distribution<> dist(0,8);

    int i=0;

    while(i<4096)
    {
        int size;
        do{
            int temp =  dist(eng);
            size = AVAILABLE_BLOCK_SIZES[temp];
        }
        while(i+size>4096);
        free_list->InsertInTail(i,size);
        i+=size;
    }
}

void * FirstFit(int size)
{
    cout<<"First Fit"<<endl;
    if(free_list->head->data2>=size)
    {
        int startAdd = free_list->head->data1;
        if(free_list->head->data2-size >0)
        {
            free_list->head->data2-=size;
            free_list->head->data1+=size;
        }
        else
        {
            free_list->head = free_list->head->next;
        }
        cout<<"Memory allocated at : "<<startAdd<<" of size "<<size<<endl;
        
        alloc_list->InsertInTail(startAdd,size,reinterpret_cast<uintptr_t>((void *)(MEMORY + startAdd)));
        return (void *)(MEMORY + startAdd);
    }
    else
    {
        Node1 *i = free_list->head,*iNext=NULL;
        if(i!=NULL)
        {
            iNext = free_list->head->next;
        }
        int startAdd;
        for(;iNext!=NULL;i = iNext,iNext = iNext->next)
        {
            if(size<=iNext->data2)
            {
                startAdd = iNext->data1;
                if(iNext->data2-size > 0)
                {
                    iNext->data2-=size;
                    iNext->data1+=size;
                }
                else
                {
                    i->next = iNext->next;
                }
                break;
            }
        }
        if(iNext==NULL)
        {
            cout<<"Malloc failed"<<endl;
            return NULL;
        }
        cout<<"Memory allocated at : "<<startAdd<<" of size "<<size<<endl;
        alloc_list->InsertInTail(startAdd,size,reinterpret_cast<uintptr_t>((void *)(MEMORY + startAdd)));

        return (void *)(MEMORY + startAdd);
    }
}

void *NextFit(int size)
{
    cout<<"Next Fit: "<<endl;
    static Node1 *start = free_list->head;
    static bool first = true;
    if(first)
    {
        if(free_list->head->data2>=size)
        {
            int startAdd = free_list->head->data1;
            if(free_list->head->data2-size>0)
            {
                free_list->head->data2-=size;
                free_list->head->data1+=size;
            }
            else
            {
                free_list->head = free_list->head->next;
            }
            cout<<"Memory allocated at : "<<startAdd<<" of size "<<startAdd<<endl;
            alloc_list->InsertInTail(startAdd,size,reinterpret_cast<uintptr_t>((void *)(MEMORY + startAdd)));
            return (void *)(MEMORY + startAdd);
            
        }
        first = false;
    }
    Node1 *i = start;
    Node1 *iNext = i->next;
    int startAdd;
    bool found =false;
    do
    {
        if(iNext==NULL)
        {
            iNext = free_list->head;
        }
        if(size<=iNext->data2)
        {
            startAdd = iNext->data1;
            cout<<"Memory allocated at : "<<startAdd<<" of size "<<size<<endl;
            if(iNext->data2-size>0)
            {
                iNext->data2-=size;
                iNext->data1+=size;
            }
            else
            {
                if(i!=NULL)
                {
                    i->next = iNext->next;
                }
                else
                {
                    free_list->head = free_list->head->next;
                }
            }
            start = i;
            found=true;
            break;
        }
        i = iNext,iNext = iNext->next;
    }while(i!=start);
    if(!found)
    {
        cout<<"Malloc failed"<<endl;
        return NULL;
    }
        alloc_list->InsertInTail(startAdd,size,reinterpret_cast<uintptr_t>((void *)(MEMORY + startAdd)));
        return (void *)(MEMORY + startAdd);
}
 
void * BestFit(int size)
{
    cout<<"Best Fit: "<<endl; 
    Node1 *minDiffNode=NULL,*minDiffPrev=NULL;
    int minDiff = 100000,startAdd;
    for(Node1* i = NULL,*iNext = free_list->head;iNext!=NULL;i=iNext,iNext = iNext->next)
    {
        if(iNext->data2-size>=0&&iNext->data2-size<minDiff)
        {
            minDiff = iNext->data2-size;
            minDiffNode = iNext;
            minDiffPrev = i;
        }
    }
    if(minDiffNode==NULL)
    {
        cout<<"Malloc failed"<<endl;
        return NULL;
    }
    
    startAdd = minDiffNode->data1;
    
    cout<<"Memory allocated at : "<<minDiffNode->data1<<" of size "<<size<<endl;
    if(minDiffNode->data2-size >0)
    {
        minDiffNode->data2-=size;
        minDiffNode->data1+=size;
    }
    else
    {
        if(minDiffPrev==NULL)
        {
            free_list->head = free_list->head->next;
        }
        else
        {
            minDiffPrev->next = minDiffNode->next;
        }
    }
    alloc_list->InsertInTail(startAdd,size,reinterpret_cast<uintptr_t>((void *)(MEMORY + startAdd)));
    return (void *)(MEMORY + startAdd);
}


void *Malloc(int size,int fitType)
{
    
     switch(fitType)
     {
         case 0:
         return FirstFit(size);
         break;
         case 1:
         return NextFit(size);
         break;
         case 2:
         return BestFit(size);
         break;
     }
}

void Free(void *pointer)
{

    Node2 *toDelete = alloc_list->FindBydata3AndDelete(reinterpret_cast<uintptr_t>(pointer));
    if(toDelete != NULL)
    {
        free_list->InsertInBetween(toDelete->data1,toDelete->data2);
        cout<<"Deleted"<<endl;
    } 
    free(toDelete);
}

void PrintFreeList()
{
    cout<<"Free List"<<endl;
    free_list->Print();
}

void PrintAllocList()
{
    cout<<"Alloc List"<<endl;
    alloc_list->Print();
}