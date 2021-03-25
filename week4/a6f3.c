/* a6f3.c */
/* iis21118 Αποστολία Μαρία Σοφιανοπούλου
   ics21138 Ανδρέας Χατζηαντώνης
   iis21027 Ευστάθιος Ιωσηφίδης
   iis21049 Αικατερίνη Γκουζέλη */

#include <stdio.h>

#define QueueLimit 10

/* Δήλωση Τύπων */

typedef int QueueElementType;

typedef struct
{
    int Front, Rear;
    int Count;
    QueueElementType Element[QueueLimit];
}QueueType;

typedef enum
{
    FALSE, TRUE
}boolean;

/* Δήλωση Συναρτήσεων */

void CreateQ(QueueType *Queue);
void RemoveQ(QueueType *Queue, QueueElementType *Item);
void AddQ(QueueType *Queue, QueueElementType Item);
void TraverseQ(QueueType Queue);
boolean EmptyQ(QueueType Queue);
boolean FullQ(QueueType Queue);

int main()
{
    QueueType mQueue;
    QueueElementType i, tmp, No;

    // Question a

    printf ("---a---\n");
    CreateQ(&mQueue);

    for (i=0; i<QueueLimit; i++)
    {
        AddQ(&mQueue, i);
    }
    TraverseQ(mQueue);
    printf ("Front=%d Rear=%d Count=%d\n", mQueue.Front, mQueue.Rear, mQueue.Count);
    
    // Question b
    
    printf ("---b---\n");
    AddQ(&mQueue, QueueLimit);
    
    printf ("\n");
    TraverseQ(mQueue);
    printf ("Front=%d Rear=%d Count=%d\n", mQueue.Front, mQueue.Rear, mQueue.Count);
    
    // Question c
    
    printf ("---c---\n");
    RemoveQ(&mQueue, &tmp);
    
    TraverseQ(mQueue);
    printf ("Removed item=%d Front=%d Rear=%d Count=%d\n", tmp, mQueue.Front, mQueue.Rear, mQueue.Count);
    
    // Question d
    
    printf ("---d---\n");
    No = 25;
    AddQ(&mQueue, No);
    
    TraverseQ(mQueue);
    printf ("Front=%d Rear=%d Count=%d\n", mQueue.Front, mQueue.Rear, mQueue.Count);
    
    // Question e
    
    printf ("---e---\n");
    AddQ(&mQueue, QueueLimit);
    printf ("\n");
    
    TraverseQ(mQueue);
    printf ("Front=%d Rear=%d Count=%d\n", mQueue.Front, mQueue.Rear, mQueue.Count);
    
    // Question f
    
    printf ("---f---\n");
    
    while (!EmptyQ(mQueue))
    {
        RemoveQ(&mQueue, &tmp);
        TraverseQ(mQueue);
        printf ("Removed item=%d Front=%d Rear=%d Count=%d\n", tmp, mQueue.Front, mQueue.Rear, mQueue.Count);
    }
    
    return 0;
}

/* Συναρτήσεις */

void CreateQ(QueueType *Queue)
{
    Queue->Front = 0;
    Queue->Rear = 0;
    Queue->Count = 0;
}

void RemoveQ(QueueType *Queue, QueueElementType *Item)
{
    if (!EmptyQ(*Queue))
    {
        *Item = Queue->Element[Queue->Front];
        Queue->Front = (Queue->Front+1)%QueueLimit;
        (Queue->Count)--;
    }
    else
        printf ("Empty Queue");
}

void AddQ(QueueType *Queue, QueueElementType Item)
{
    if (!FullQ(*Queue))
    {
        Queue->Element[Queue->Rear] = Item;
        Queue->Rear = (Queue->Rear+1)%QueueLimit;
        (Queue->Count)++;
    }
    else
        printf ("Full Queue");
}

void TraverseQ(QueueType Queue)
{
    int c;
    
    c = Queue.Front;
    printf ("Queue: ");
    
    if (EmptyQ(Queue))
    {
        printf ("Empty Queue");
    }
    
    while (c != Queue.Rear || Queue.Count != 0)
    {
        printf ("%d ", Queue.Element[c]);
        c = (c+1)%QueueLimit;
        (Queue.Count)--;
    }
    
    printf ("\n");
}

boolean EmptyQ(QueueType Queue)
{
    return (Queue.Count == 0);
}

boolean FullQ(QueueType Queue)
{
    return (Queue.Count == QueueLimit);
}