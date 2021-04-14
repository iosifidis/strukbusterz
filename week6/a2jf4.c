/* a2jf4.c */
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

void insert_list_m_elements(ListPointer *List, int n);
void CreateList(ListPointer *List);
void LinkedInsert(ListPointer *List, ListElementType Item, ListPointer PredPtr);
void LinkedDelete(ListPointer *List, ListPointer PredPtr);
void LinkedTraverse(ListPointer List);
void LinearSearch(ListPointer List, ListElementType Item, ListPointer *PredPtr, boolean *Found);
void OrderedLinearSearch(ListPointer List, ListElementType Item, ListPointer *PredPtr, boolean *Found);
boolean EmptyList(ListPointer List);

int main()
{
    ListPointer AList;
    ListElementType Item;
    int i, n;
    
    CreateList(&AList);

    printf ("DWSE TO PLH8OS TWN STOIXEIWN THS LISTAS: ");
    scanf("%d",&n);

    for (i=0; i<n; i++)
    {
        printf ("DWSE TON ARI8MO GIA EISAGWGH STHN ARXH THW LISTAS: ");
        scanf("%d", &Item);
        LinkedInsert(&AList, Item, NULL);
    }

    printf ("*********Arxiki lista************\n");
    LinkedTraverse(AList);
    printf ("\n");

    printf ("DWSE TI THESI, META APO TIN OPOIA THA EISAXTHOUN TA STOIXEIA: ");
    scanf("%d", &n);
    insert_list_m_elements (&AList, n);

    printf ("*********Teliki lista************\n");
    LinkedTraverse(AList);
    printf ("\n");
    

    return 0;
}

/* Συναρτήσεις */

void insert_list_m_elements(ListPointer *List, int n)
{
    ListPointer TempPtr;
    int i, j, m;

    if (EmptyList(*List))
    {
        printf ("EMPTY LIST");
    }
    else 
    {
        TempPtr = *List;
        i = 1; // μετράει τη "θέση" του τρέχοντος στοιχείου στη ΣΛ

        while (TempPtr->Next!=NULL && i<n)
        {
            TempPtr = TempPtr->Next;
            i++;
        }
    }

    // η ΣΛ εχει λιγότερα στοιχεία από n αν τερματίσει ο βρόχος πριν φτάσουμε στη θέση n

    if (i<n || n<1)
    {
        printf ("ERROR\n");
    }
    else 
    {
        printf ("DWSE TO PLH8OS TWN STOIXEIWN THS LISTAS: ");
        scanf("%d", &m);
        for (i=0; i<m; i++)
        {
            printf ("DWSE TON ARI8MO GIA EISAGWGH STHN ARXH THS LISTAS: ");
            scanf("%d", &j);

            // Στην 1η επανάληψη το TempPtr (τρέχον στοιχείο) είανι το στοιχείο στη θέση n ΣΛ (απο τον προηγούμενο βρόχο)

            LinkedInsert(List, j, TempPtr);
            TempPtr = TempPtr->Next;
        }
    }
}

void CreateList(ListPointer *List)
{
	*List = NULL;
}

boolean EmptyList(ListPointer List)
{
	return (List==NULL);
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