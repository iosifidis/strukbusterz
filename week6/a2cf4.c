/* a2cf4.c */
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

void concat_list(ListPointer AList, ListPointer BList, ListPointer *FinalList);
void CreateList(ListPointer *List);
void LinkedInsert(ListPointer *List, ListElementType Item, ListPointer PredPtr);
void LinkedDelete(ListPointer *List, ListPointer PredPtr);
void LinkedTraverse(ListPointer List);
void LinearSearch(ListPointer List, ListElementType Item, ListPointer *PredPtr, boolean *Found);
void OrderedLinearSearch(ListPointer List, ListElementType Item, ListPointer *PredPtr, boolean *Found);
boolean EmptyList(ListPointer List);

int main()
{
    ListPointer AList, BList, FinalList;
    ListElementType item;
    int i, n, m;

    CreateList(&AList);
    CreateList(&BList);
    CreateList(&FinalList);

    printf ("DWSE TO PLI8OS TWN STOIXEIWN THS LISTAS 1: ");
    scanf ("%d", &n);
    printf ("\n");

    for (i=0; i<n; i++)
    {
        printf ("DWSE TON ARI8MO GIA EISAGWGH STHN ARXH THS LISTAS 1: ");
        scanf ("%d", &item);
        printf ("\n");
        LinkedInsert(&AList, item, NULL);
    }

    printf ("DWSE PLI8OS TWN STOIXEIWN THS LISTAS 2: ");
    scanf ("%d", &m);
    printf ("\n");

    for (i=0; i<m; i++)
    {
        printf ("DWSE TON ARI8MO GIA EISAGWGH STHN ARXH THS LISTAS 2: ");
        scanf ("%d", &item);
        printf ("\n");
        LinkedInsert(&BList, item, NULL);
    }

    printf ("LISTA 1:\n");
    LinkedTraverse(AList);
    printf ("\n");
    printf ("LISTA 2:\n");
    LinkedTraverse(BList);
    printf ("\n");
    concat_list(AList, BList, &FinalList);
    printf ("SYNENWMENH LISTA:\n");
    LinkedTraverse(FinalList);
    printf ("\n");


    return 0;
}

/* Συναρτήσεις */

void concat_list(ListPointer AList, ListPointer BList, ListPointer *FinalList)
{
    ListPointer CurrPtr;

    CurrPtr = AList;

    while (CurrPtr != NULL)
    {
        // Διασχίζεται η 1η λίστα και τα στοίχεια της εισάγονται ένα-ένα στην τελική λίστα 
        
        LinkedInsert(FinalList, CurrPtr->Data, NULL);
        CurrPtr = CurrPtr->Next;
    }

    CurrPtr = BList;

    while (CurrPtr != NULL)
    {
        // Διασχίζεται η 2η λίστα και τα στοίχεια της εισάγονται ένα-ένα στην τελική λίστα

        LinkedInsert(FinalList, CurrPtr->Data, NULL);
        CurrPtr = CurrPtr->Next;
    }
}

void CreateList(ListPointer *List)
{
    *List = NULL;
}

void LinkedInsert(ListPointer *List, ListElementType Item, ListPointer PredPtr)
{
	ListPointer TempPtr;

   TempPtr= (ListPointer)malloc(sizeof(struct ListNode));
   TempPtr->Data = Item;
	if (PredPtr==NULL) {
        TempPtr->Next = *List;
        *List = TempPtr;
    }
    else {
        TempPtr->Next = PredPtr->Next;
        PredPtr->Next = TempPtr;
    }
}

void LinkedDelete(ListPointer *List, ListPointer PredPtr)
{
    ListPointer TempPtr;

    if (EmptyList(*List))
   	    printf("EMPTY LIST\n");
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
   	    printf("EMPTY LIST\n");
   else
   {
   	    CurrPtr = List;
         while ( CurrPtr!=NULL )
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