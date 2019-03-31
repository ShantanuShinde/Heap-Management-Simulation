#include<iostream>
#include<cstdint>

struct Node1
{
    int data1,data2;
    Node1* next;
};

struct List
{
    Node1 *head;
    Node1 *tail;
    List();
    void InsertInTail(int data1,int data2);
    void InsertInBetween(int data1,int data2);
    void Print();
};

struct Node2
{
    int data1,data2;
    uintptr_t data3;
    Node2* next;
};

struct List2
{
    Node2 *head,*tail;
    List2();
    Node2 *FindBydata3AndDelete(uintptr_t data);
    void InsertInTail(int data1,int data2,uintptr_t data3);
    void Print();
};