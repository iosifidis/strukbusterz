/* a2ρf4.c */
/* iis21118 Αποστολία Μαρία Σοφιανοπούλου
   ics21138 Ανδρέας Χατζηαντώνης
   iis21027 Ευστάθιος Ιωσηφίδης
   iis21049 Αικατερίνη Γκουζέλη */

#include <stdio.h>
#include <stdlib.h>

/* Δήλωση Τύπων */

typedef int ListElementType;
typedef struct ListNode *ListPointer;
typedef struct ListNode
{
	ListElementType Data;
    ListPointer Next;
} ListNode;

typedef enum {
    FALSE, TRUE
} boolean;

/* Δήλωση Συναρτήσεων */

void CreateList(ListPointer *List);
void LinkedInsert(ListPointer *List, ListElementType Item, ListPointer PredPtr);
void LinkedDelete(ListPointer *List, ListPointer PredPtr);
void LinkedTraverse(ListPointer List);
void LinearSearch(ListPointer List, ListElementType Item, ListPointer *PredPtr, boolean *Found);
void OrderedLinearSearch(ListPointer List, ListElementType Item, ListPointer *PredPtr, boolean *Found);
boolean EmptyList(ListPointer List);
ListElementType RemoveMins(ListPointer *InList);

int main()
{
    ListPointer AList;
    ListElementType Item, min;
    int i, n;

    CreateList(&AList); //Δημιουρία κενής ΣΛ
    printf ("DWSE TO PLH8OS TWN STOIXEIWN THS LISTAS: ");
    scanf ("%d", &n);

    for (i=0; i<n; i++)
    {
        printf ("DWSE TON ARI8MO GIA EISAGWGH STHN ARXH THS LISTAS 1: ");
        scanf ("%d", &Item);
        LinkedInsert(&AList, Item, NULL);
    }

    printf ("Traversing list\n");
    LinkedTraverse(AList); //Εμφάνιση των στοιχείων της ΣΛ
    printf("\n");

    printf ("Removing min from list\n");
    min = RemoveMins(&AList);
    printf ("Min was %d\n", min);

    printf ("Traversing list with min removed\n");
    LinkedTraverse(AList);
    printf ("\n");


    return 0;
}

/* Συναρτήσεις */

void CreateList(ListPointer *List)
{
    *List = NULL;
}

void LinkedInsert(ListPointer *List, ListElementType Item, ListPointer PredPtr)
{
    ListPointer TempPtr;

    TempPtr = (ListPointer)malloc(sizeof(struct ListNode));
    TempPtr->Data = Item;
    if (PredPtr == NULL)
    {
        TempPtr->Next = *List;
        *List = TempPtr;
    }
    else 
    {
        TempPtr->Next = PredPtr->Next;
        PredPtr->Next = TempPtr;
    }
}

void LinkedDelete(ListPointer *List, ListPointer PredPtr)
{
    ListPointer TempPtr;

    if (EmptyList(*List))
    {
        printf ("EMPTY LIST\n");
    }
    else 
    {
        if (PredPtr == NULL)
        {
            TempPtr = *List;
            *List = TempPtr->Next;
        }
        else
        {
            TempPtr = PredPtr->Next;
            PredPtr->Next = TempPtr->Next;
        }
        free(TempPtr);
    }
}

void LinkedTraverse(ListPointer List)
{
    ListPointer CurrPtr;

    if (EmptyList(List))
    {
        printf ("EMPTY LIST\n");
    }
    else 
    {
        CurrPtr = List;
        while (CurrPtr != NULL)
        {
            printf ("%d ", CurrPtr->Data);
            CurrPtr = CurrPtr->Next;
        }
    }
}

void LinearSearch(ListPointer List, ListElementType Item, ListPointer *PredPtr, boolean *Found)
{
    ListPointer CurrPtr;
   boolean stop;

   CurrPtr = List;
   *PredPtr=NULL;
   stop= FALSE;

   while (!stop && CurrPtr!=NULL )
    {
        if (CurrPtr->Data==Item )
         	stop = TRUE;
        else
        {
            *PredPtr = CurrPtr;
            CurrPtr = CurrPtr->Next;
        }
	}
	*Found=stop;
}

void OrderedLinearSearch(ListPointer List, ListElementType Item, ListPointer *PredPtr, boolean *Found)
{
    ListPointer CurrPtr;
   boolean DoneSearching;

   CurrPtr = List;
   *PredPtr = NULL;
   DoneSearching = FALSE;
   *Found = FALSE;

   while (!DoneSearching && CurrPtr!=NULL )
    {
         if (CurrPtr->Data>=Item )
         {
         	DoneSearching = TRUE;
         	*Found = (CurrPtr->Data==Item);
         }
         else
         {
         	*PredPtr = CurrPtr;
            CurrPtr = CurrPtr->Next;
         }
	}
}

boolean EmptyList(ListPointer List)
{
    return (List == NULL);
}

ListElementType RemoveMins(ListPointer *InList)
{
    ListPointer CurrPtr, PredPtr;
    ListElementType min;

    CurrPtr = *InList;
    min = CurrPtr->Data;

    while (CurrPtr != NULL)
    {
        if (CurrPtr->Data < min)
        {
            min = CurrPtr->Data;
        }
        CurrPtr = CurrPtr->Next;
    }

    // Διάσχιση της ΣΛ και διαγραφή όλων των στοιχείων με τιμή ίση με το ελάχιστο

    CurrPtr = *InList;
    PredPtr = NULL;

    while (CurrPtr != NULL)
    {
        if (CurrPtr->Data == min)
        {
            CurrPtr = CurrPtr->Next;
            LinkedDelete(InList, PredPtr);
        }
        else
        {
            PredPtr = CurrPtr;
            CurrPtr = CurrPtr->Next;
        }
    }

    return min;
}