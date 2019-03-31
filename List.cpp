#include"List.h"
#include<iostream>

List::List()
{
    head = NULL;
    tail = NULL;
}

void List::InsertInTail(int data1,int data2)
{
    if(head==NULL)
    {
        head = tail = new Node1;
        head->next = NULL;
        head->data1 = data1;
        head->data2 = data2;
    }
    else
    {
        Node1 *temp = new Node1;
        temp->data1 = data1;
        temp->data2 = data2;
        tail->next = temp;
        tail = tail->next;
        tail->next = NULL;
    }
    
}

void List::InsertInBetween(int data1,int data2)
{
    if(head->data1>data1)
    {
        if(head->data1==data1+data2)
        {
            head->data1 = data1;
            head->data2 += data2;
        }
        else
        {
            Node1 *newNode = new Node1;
            newNode->data1 = data1;newNode->data2 = data2;
            newNode->next = head;
            head = newNode;
        }
    }
    else
    {
        for(Node1 *i = head,*iN = head->next;iN!=NULL;i = iN,iN = iN->next)
        {
            if(data1<iN->data1&&data1>i->data1)
            {
                if(iN->data1 = data1+data2)
                {
                    iN->data1 = data1;
                    iN->data2 +=data2;
                }
                else if (i->data1==data1-i->data2) 
                {
                    i->data2 += data2;
                }
                
                else
                {
                    Node1 *newNode = new Node1;
                    newNode->data1 = data1;newNode->data2 = data2;
                    newNode->next = iN;
                    i->next = newNode;
                }
                return;
            }
            if(data1>tail->data1)
            {
                if(tail->data1= data1 - i->data2)
                {
                    tail->data2 += data2;
                }
                else
                {
                    Node1 *newNode = new Node1;
                    newNode->data1 = data1; newNode->data2 = data2;
                    newNode->next = NULL;
                    tail->next = newNode;
                    tail = newNode;
                }
            }
        }
    }
    
}

void List::Print()
{
    for(Node1 *i=head;i!=NULL;i=i->next)
    {
        std::cout<<i->data1<<"|"<<i->data2<<std::endl;
    }
}

List2::List2()
{
    head = NULL;
    tail = NULL;
}

void List2::InsertInTail(int data1,int data2,uintptr_t data3)
{
    if(head==NULL)
    {
        head = tail = new Node2;
        head->next = NULL;
        head->data1 = data1;
        head->data2 = data2;
        head->data3 = data3;
    }
    else
    {
        Node2 *temp = new Node2;
        temp->data1 = data1;
        temp->data2 = data2;
        temp->data3 = data3;
        tail->next = temp;
        tail = tail->next;
        tail->next = NULL;

        
    }
}

Node2 *List2::FindBydata3AndDelete(uintptr_t data)
{
    if(head->data3==data)
    {
        Node2 *temp = head;
        head = head->next;
        return temp;
    }
    for(Node2 *i = head,*iN = head->next;iN!=NULL;i=iN,iN = iN->next)
    {
        if(iN->data3==data)
        {
            Node2 *temp = iN;
            i->next = iN->next;
            delete iN;
            return temp;
        }
    }
    return NULL;
}

void List2::Print()
{
    for(Node2 *i=head;i!=NULL;i=i->next)
    {
        std::cout<<i->data1<<"|"<<i->data2<<"|"<<i->data3<<std::endl;
    }
}