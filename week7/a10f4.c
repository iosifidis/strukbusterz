/* a10f4.c */
/* iis21118 Αποστολία Μαρία Σοφιανοπούλου
   ics21138 Ανδρέας Χατζηαντώνης
   iis21027 Ευστάθιος Ιωσηφίδης
   iis21049 Αικατερίνη Γκουζέλη */

#include <stdio.h>
#include <stdlib.h>

typedef int StackElementType;
typedef struct StackNode *StackPointer;
typedef struct StackNode
{
	StackElementType Data;
    StackPointer Next;
} StackNode;

typedef enum {
    FALSE, TRUE
} boolean;

void CreateStack(StackPointer *Stack);
boolean EmptyStack(StackPointer Stack);
void Push(StackPointer *Stack, StackElementType Item);
void Pop(StackPointer *Stack, StackElementType *Item);
void TraverseStack(StackPointer Stack);

int main()
{
    StackPointer AStack1, AStack2;
    StackElementType Item;
    int plithos,i;

    CreateStack(&AStack1);  //Δημιουργώ τη στοίβα AStack1
    CreateStack(&AStack2);  //Δημιουργώ τη στοίβα AStack2

    printf("PLITHOS STOIXEIWN: ");
    scanf("%d", &plithos);  //Διαβάζω το πλήθος των στοιχείων που θα εισαχθούν στη στοίβα
    for(i=0;i<plithos;i++)
    {
        printf("DWSE TO 1o STOIXEIO: ");
        scanf("%d", &Item);
        Push(&AStack1, Item);
    }

    printf("*********1i stoiva***********\n");
    TraverseStack(AStack1);  //Εμφανίζω τα στοιχεία της στοίβας AStack1

    while(!EmptyStack(AStack1))
    {
        Pop(&AStack1, &Item);  //Απωθώ το κορυφαίο στοιχείο Item από τη στοίβα AStack1
        Push(&AStack2, Item);  //Εισάγω στο στοιχείο Item στη στοίβα AStack2
    }

    printf("*********2i stoiva***********\n");
    TraverseStack(AStack2);  //Εμφανίζω τα στοιχεία της στοίβας AStack2

    return 0;
    system("PAUSE");

}


void CreateStack(StackPointer *Stack)
{
	*Stack = NULL;
}

boolean EmptyStack(StackPointer Stack)
{
	return (Stack==NULL);
}

void Push(StackPointer *Stack, StackElementType Item)
{
	StackPointer TempPtr;

    TempPtr= (StackPointer)malloc(sizeof(struct StackNode));
    TempPtr->Data = Item;
    TempPtr->Next = *Stack;
    *Stack = TempPtr;
}

void Pop(StackPointer *Stack, StackElementType *Item)
{
    StackPointer TempPtr;

    if (EmptyStack(*Stack)) {
   	    printf("EMPTY Stack\n");
    }
   else
   {
        TempPtr = *Stack;
        *Item=TempPtr->Data;
        *Stack = TempPtr->Next;
        free(TempPtr);
    }
}

void TraverseStack(StackPointer Stack)
{
    StackPointer CurrPtr;

   if (EmptyStack(Stack))
   {
           printf("EMPTY Stack\n");
    }
   else
   {
           CurrPtr = Stack;
         while ( CurrPtr!=NULL )
        {
               printf("%d ", CurrPtr->Data);
             CurrPtr = CurrPtr->Next;
        }
   }
    printf("\n");
}

